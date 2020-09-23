/**
 An interface that describes the operations of a bag of strings.
 */
public interface BagOfStringsInterface
{
    /** Task: Gets the capacity of the bag.
     @return the integer n (umber of strings that the bag can hold */
    public int getCapacity();

    /** Task: Gets the current number of strings in the bag.
     @return the integer number of strings currently in the bag */
    public int getCurrentSize();

    /** Task: Sees whether the bag is full.
     @return true if the bag is full, or false if not */
    public boolean isFull();

    /** Task: Sees whether the bag is empty.
     @return true if the bag is empty, or false if not */
    public boolean isEmpty();

    /** Task: Adds a new string to the bag.
     @param newString the string to be added
     @return true if the addition is successful, or false if not */
    public void add(String newString) throws BagOfStringsException;

    /** Task: Removes all strings from the bag. */
    public void clear();

    /** Task: Removes one unspecified string from the bag.
     @return either the removed string, if the removal
     was successful, or null */
    public String remove();

    /** Task: Removes one occurrence of a particular string from
     the bag, if possible.
     @param aString the string to be removed
     @return true, if the removal was successful, or false if not */
    public void remove(String aString) throws BagOfStringsException;

    /** Task: Counts the number of times a given string appears in a bag.
     @param aString the string to be counted
     @return the number of times aString appears in the bag */
    public int getFrequencyOf(String aString);

    /** Task: Tests whether the bag contains a given string.
     @param aString the string to locate
     @return true if the bag contains aString, or false otherwise */
    public boolean contains(String aString);

    /** Task: Retrieves all strings that are in the bag.
     @return a newly allocated array of all the strings in the bag */
    public String[] toArray();

} // end BagOfStringsInterface