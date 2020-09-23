/**
 A class that implements a bag of strings by using an array.
 */
public class BagOfStrings implements BagOfStringsInterface
{
    private final String[] bag;
    private static final int DEFAULT_CAPACITY = 10;
    private int numberOfStrings;
    
    /** Task: Creates an empty bag whose capacity is 25. */
    public BagOfStrings()
    {
        this (DEFAULT_CAPACITY);
    } // end default constructor
	
	
    /** Task: Creates an empty bag having a given capacity.
	 @param capacity the integer capacity desired */
    public BagOfStrings(int capacity)
    {
        bag = new String[capacity];
        numberOfStrings = 0;
    } // end constructor
	
	
    /** Task: Adds a new string to this bag.
	 @param newString the string to be added
	 @return true if the addition is successful, or false if not */
    @Override
    public void add(String newString) throws BagOfStringsException
    {
        if (!isFull())
        { // assertion: result is true here
            bag[numberOfStrings] = newString;
            numberOfStrings++;
        }
        else{
            throw new BagOfStringsException();
        }
    } // end add
	
	
    /** Task: Retrieves all strings that are in this bag.
	 @return a newly allocated array of all the strings in the this */
    @Override
    public String[] toArray()
    {
        String[] result = new String[numberOfStrings];
        System.arraycopy(bag, 0, result, 0, numberOfStrings);
        return result;
    } // end toArray
	
	
    /** Task: Sees whether this bag is full.
	 @return true if this bag is full, or false if not */
    @Override
    public boolean isFull()
    {
        return numberOfStrings == bag.length;
    } // end isFull
	
	
    /** Task: Sees whether this bag is empty.
	 @return true if the bag is empty, or false if not */
    @Override
    public boolean isEmpty()
    {
        return numberOfStrings == 0;
    } // end isEmpty
	
	
    /** Task: Gets the capacity of this bag.
	 @return the integer number of strings that this bag can hold */
    @Override
    public int getCapacity()
    {
        return bag.length;
    } // end getCapacity
	
	
    /** Task: Gets the number of strings currently in this bag.
	 @return the integer number of strings currently in this bag */
    @Override
    public int getCurrentSize()
    {
        return numberOfStrings;
    } // end getCurrentSize
	
    
    /** Task: Counts the number of times a given string appears
	 in this bag.
	 @param aString the string to be counted
	 @return the number of times aString appears in this bag */
    @Override
   public int getFrequencyOf(String aString)
    {
        int counter = 0;
        for (int index = 0 ; index < numberOfStrings; index++)
        {
            if (aString.equals(bag[index]))
            {
                counter++;
            } // end if
        } // end for
        return counter;
    } // end getFrequencyOf
	
	
    /** Task: Tests whether this bag contains a given string.
	 @param aString the string to locate
	 @return true if this bag contains aString, or false otherwise */
    @Override
    public boolean contains(String aString)
    {
        return getIndexOf(aString) > -1;
    } // end contains
	
	
    /** Task: Removes all strings from this bag. */
    @Override
    public void clear()
    {
        while (!isEmpty())
            remove();
    } // end clear
	
	
    /** Task: Removes one unspecified string from this bag.
	 @return either the removed string, if the removal
	 was successful, or null otherwise */
    @Override
    public String remove()
    {
        
        String result = removeEntry(numberOfStrings - 1);
        return result;
    } // end remove
	
    
    
  
	
    /** Task: Removes one occurrence of a given string from this bag.
	 @param aString the string to be removed
	 @return either the removed string, if the removal
	 was successful, or null otherwise */
    @Override
    public void remove(String aString) throws BagOfStringsException
    {
        
        int index = getIndexOf(aString);
        if(index == -1){
            throw new BagOfStringsException();
        }
        String result = removeEntry(index);
        
        
        if(!aString.equals(result)){
            throw new BagOfStringsException();
        }
    } // end remove// end remove
	
	
    // Locates a given string within the array bag.
    // Returns the index of the string, if located, or -1 otherwise.
    private int getIndexOf(String aString)
    {
        int where = -1;
        boolean stillLooking = true;
        int index = 0 ;
        while (stillLooking && (index < numberOfStrings))
        {
            if (aString.equals(bag[index]))
            {
                stillLooking = false;
                where = index;
            }
            else
            {
                index++;
            } // end if
        } // end for
        return where;
    } // end getIndexOf
	
	
    // Removes and returns the array entry at a given index.
    // If no such entry exists, returns null.
    private String removeEntry(int givenIndex)
    {
        String result = null;
        if (!isEmpty() && (givenIndex >= 0))
        {
            result = bag[givenIndex]; // entry to remove
            numberOfStrings--;
            bag[givenIndex] = bag[numberOfStrings]; //replace entry to
            //remove with last entry
            bag[numberOfStrings] = null; // remove reference to last entry
        } // end if
        return result;
    } // end removeEntry
} // end BagOfStrings