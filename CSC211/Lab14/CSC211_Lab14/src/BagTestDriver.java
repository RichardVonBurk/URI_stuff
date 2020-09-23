import java.util.Random;
public class BagTestDriver {

    public BagTestDriver()
    {
    } // end main

    public void testBag()
    {
        Random generator = new Random();
        BagOfStringsInterface testBag = new BagOfStrings();
        showBagStats(testBag);

        String[] testValues = { "A", "B", "C", "D", "A", "A", "D", "D", "A", "A", "D", "Z" };
        addToBag(testBag, testValues);
        displayBag(testBag);

        testBag.clear();
        for (String testItem : testValues) {
            addAndCheck(testBag, testItem);
        }
        showBagStats(testBag);

        for (String testItem : testValues) {
            int randomIndex = generator.nextInt(testValues.length + 1);
            if (randomIndex >= testValues.length)
                removeFromBag(testBag, null);
            else
                removeFromBag(testBag, testValues[randomIndex]);
        } // end for
       removeFromBag(testBag, null);
       removeFromBag(testBag, null);
       removeFromBag(testBag, null);
 
    }

    // Additional testing helper methods are implemented here . . . 
    private void showBagStats(BagOfStringsInterface aBag)
    {
        int capacity = aBag.getCapacity();
        int size = aBag.getCurrentSize();
        System.out.print("Maximum capacity of " + capacity);
        System.out.println(" and a current item count of " + size);

        if (aBag.isEmpty())
                System.out.print("The bag is empty and ");
        else
                System.out.print("The bag is not empty and ");

        if (aBag.isFull())
                System.out.println("it is full.");
        else
                System.out.println("it is not full.");
    } // end showBagStats

    private void displayBag(BagOfStringsInterface aBag)
    {
        System.out.print("The bag contains: ");
        String[] bagArray = aBag.toArray();
        for (String bagItem : bagArray) {
            System.out.print(bagItem + " ");
        } // end for
        System.out.println();
    } // end displayBag

    // Add one item and validate that it was added
    private void addAndCheck(BagOfStringsInterface aBag, String aString)
    {
        System.out.print("Adding \"" + aString + "\" to the bag ");
        try{
            
            aBag.add(aString);
            if (aBag.contains(aString))
                System.out.println("succeeded.");
            else
                System.out.println("failed.");
            
        }
        catch(BagOfStringsException e){
            System.out.print(e.getMessage());
        }
        
        
    } // end addAndCheck

    // Add an array of String to the bag
    private void addToBag (BagOfStringsInterface aBag, String[] content)
    {
        for (String bagItem : content) {
            try{
                aBag.add(bagItem);
            }catch(BagOfStringsException e){
                System.out.print(e.getMessage());
            }
        } // end for
    } // end addToBag
    //Remove an item from the bag
    private void removeFromBag(BagOfStringsInterface aBag, String aString)
    {
        if (aString == null)
        {
            System.out.println("\nRemoving a string from the bag:");
            String removedString = aBag.remove();
            System.out.println("\tremove() returns " + removedString);
        }
        else
        {
            System.out.println("\nRemoving \"" + aString 
                                               + "\" from the bag:");
            try{
                aBag.remove(aString);
            }
            catch(BagOfStringsException e){
                System.out.print(e.getMessage());
            }
           
        } // end if
    } // end removeFromBag
} // end class BagTestDriver