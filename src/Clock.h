#ifndef CLOCK_H
#define	CLOCK_H

class Clock {
private:
    int counter;
public:
    Clock();
    Clock(const Clock& orig);
    virtual ~Clock();
    
    int GetCounter() const {
        return counter;
    }

    void SetCounter(int counter) {
        this->counter = counter;
    }


     

};

#endif	/* CLOCK_H */

