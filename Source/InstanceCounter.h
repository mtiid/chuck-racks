//
//  InstanceCounter.h
//  ChuckRacks
//
//  Created by Jacob Penn on 2/2/17.
//
//

#ifndef InstanceCounter_hpp
#define InstanceCounter_hpp

/**
    instanceCounter is a simple class which should be used as 
    a shared resource pointer to keep a count across plugins
 
    note: this only works assuming that the host will open multiple
    instances of your plugin on the same thread
 
    @see SharedResourcePointer
 */

class instanceCounter
{
public:
    
    /** Default Constructor */
    instanceCounter();
    
    /** Default Destructor */
    ~instanceCounter();
    
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
