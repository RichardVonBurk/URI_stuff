

public class Textbook {
    
    private int pageCount;
    private String subject = "Object-Oriented Programming";       //variables
    private int unreadPages = pageCount;                                // unreadPages will start at whatever pageCount does
    
    
    public Textbook() {    
}
    public Textbook(String customSubject) {
        subject = customSubject;
}
    public Textbook(String customSubject, int customPageCount) {
        subject = customSubject;
        pageCount = customPageCount;  
}

                                    //total pages in textbook
    
    
    public String getSubject(){         
        return subject;
    }
    
    public int getPageCount(){
        return pageCount;
    }
    

    public double getWeight(){
        
        final double PAGE_WEIGHT = 0.0025;              //weight of book is in kgs
        double weight = pageCount * PAGE_WEIGHT;
        return weight;
    }
    
    public int readPages(int numPages){   //input number of pages to be read, output knowledgeGained
        
        final int PAGE_KNOWLEDGE = 5;                                 //knowledge per page
        final int REDUCED_PAGE_KNOWLEDGE = (PAGE_KNOWLEDGE /2);       //reduced is used for when pages are re-read
        int knowledgeGained;
        
        if (numPages > unreadPages){      //used if student will be re-reading pages
            int reviewedKnowledge = REDUCED_PAGE_KNOWLEDGE * Math.abs(unreadPages - numPages);      //calculates pages that are re-read
            knowledgeGained = (unreadPages * PAGE_KNOWLEDGE) + reviewedKnowledge;                   //adds knowledge gained from reading and re-reading
            unreadPages = 0;            //there cant be any unreadPages after the book has been read
        }
        
        else {      //used if student will only be reading unread pages
            unreadPages -= numPages;        //reduce unreadpages by read pages
            knowledgeGained = PAGE_KNOWLEDGE * numPages;
        }
              
        return knowledgeGained;
        
    }
    
    public int getUnreadPageCount(){
        return unreadPages;        
    }
    
}