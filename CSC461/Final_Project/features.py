import os
from collections import OrderedDict
import numpy as np
from astropy.table import Table
from cesium.time_series import TimeSeries
import cesium.featurize as featurize
from tqdm import trange, tqdm
import schwimmbad
import multiprocessing
import sklearn

import warnings
warnings.simplefilter('ignore')

pbmap = OrderedDict([ (0, 'u'), (1, 'g'), (2, 'r'), (3, 'i'),
    (4, 'z'), (5, 'y')])

# it also helps to have passbands associated with a color
pbcols = OrderedDict([(0,'blueviolet'), (1,'green'), (2,'red'),\
                      (3,'orange'), (4, 'black'), (5, 'brown')])

pbnames = list(pbmap.values())

datadir = 'data'
metafilename = f'{datadir}/training_set_metadata.csv'
# Read the metadata file into an astropy table
metadata = Table.read(metafilename, format='csv')
nobjects = len(metadata)
labels = sorted(set(metadata['target']))


def read_lightcurves():
    # Load the light curve data from csv file to an Astropy table
    lcfilename = f'{datadir}/training_set.csv'
    lcdata = Table.read(lcfilename, format='csv')

    # Now we make a cesium Timeseries object for each light curve
    tsdict = OrderedDict()
    for i in trange(nobjects, desc="Building Timeseries"):
        row = metadata[i]
        thisid = row['object_id']
        target = row['target']

        meta = {'z': row['hostgal_photoz'], 'zerr': row['hostgal_photoz_err'],
                'mwebv': row['mwebv']}

        ind = (lcdata['object_id'] == thisid)
        thislc = lcdata[ind]

        pbind = [(thislc['passband'] == pb) for pb in pbmap]
        t = [thislc['mjd'][mask].data for mask in pbind ]
        m = [thislc['flux'][mask].data for mask in pbind ]
        e = [thislc['flux_err'][mask].data for mask in pbind ]

        tsdict[thisid] = TimeSeries(t=t, m=m, e=e, label=target,
                name=thisid, meta_features=meta, channel_names=pbnames )

    del lcdata
    return tsdict

features_to_use = ["amplitude",
                   "percent_beyond_1_std",
                   "maximum",
                   "max_slope",
                   "median",
                   "median_absolute_deviation",
                   "percent_close_to_median",
                   "minimum",
                   "skew",
                   "std",
                   "weighted_average"]

def compute_or_read_features():
    featurefile = f'{datadir}/plasticc_featuretable.npz'

    def worker(tsobj):
        global features_to_use
        thisfeats = featurize.featurize_single_ts(tsobj,
                features_to_use=features_to_use, raise_exceptions=False)
        return thisfeats

    if os.path.exists(featurefile):
        featuretable, _ = featurize.load_featureset(featurefile)
    else:
        light_curves = read_lightcurves(datadir)
        features_list = []
        with tqdm(total=nobjects, desc="Computing Features") as pbar:
            with multiprocessing.Pool() as pool:
                results = pool.imap(worker, list(light_curves.values()))
                for res in results:
                    features_list.append(res)
                    pbar.update()

        featuretable = featurize.assemble_featureset(features_list=features_list,
                time_series=light_curves.values())
        # Save the computed feature set to a file
        featurize.save_featureset(fset=featuretable, path=featurefile)

    # convert cesium's MultiIndex to an AstroPy Table that is better supported by
    # scikit-learn
    old_names = featuretable.columns.values
    new_names = ['{}_{}'.format(x, pbmap.get(y, 'meta')) for x, y in old_names]
    cols = [featuretable[col] for col in old_names]
    allfeats = Table(cols, names=new_names)
    del featuretable

    return allfeats
