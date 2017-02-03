//
//  InstanceCounter.h
//  ChuckRacks
//
//  Created by Jacob Penn on 2/2/17.
//
//

#ifndef Counter_hpp
#define Counter_hpp

/**
    Counter is a simple class which can be used as
    a shared resource pointer to keep a count across plugins
 
    note: this only works assuming that the host will open multiple
    instances of your plugin on the same process
 
    @see SharedResourcePointer
 */

class Counter
{
public:
    
    /** Default Constructor */
    Counter();
    
    /** Default Destructor */
    ~Counter();
    
    /** add one to the count */
    void incrementCount();
    
    /** remove one from the count */
    void decrementCount();
    
    /** function for returning the count */
    int getCount();
    
private:
    int mCount;
};

#endif /* InstanceCounter_hpp */
