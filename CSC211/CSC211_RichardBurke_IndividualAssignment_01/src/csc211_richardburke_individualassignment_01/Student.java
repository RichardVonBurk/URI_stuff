
package csc211_richardburke_individualassignment_01;

public class Student {
    
    String name;
    
    public Student(){       //default constructor with default name
       name = "Pat Zhang-Garcia";        
    }
    
    
    Textbook book = new Textbook();     //book object is part of student
    final double HEALTH = 1.0;          
    double currentHealth = HEALTH;      //since HEALTH and KNOWLEDGE must always start at a constant other variables
    final int KNOWLEDGE = 0;            //are used if the values need to change without changing the starting point
    int currentKnowledge = KNOWLEDGE;
    
    
    public void setName(String name){   //input changes the name of student
        this.name = name;
    }
    
    public String getName(){
        return name;
    }
    
    public String getBook(){
        return book.subject;
    
    }
    
    public double getHealth(){
        return currentHealth;
    }
    
    public int getKnowledge(){
        return currentKnowledge;
        
    }
    
    public void learnSomething(int numPages){       //calls the book readpages method and adds knowledge to value
       int knowledgeGained = book.readPages(numPages);
       currentKnowledge += knowledgeGained;
    }
}
