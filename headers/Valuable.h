#ifndef VALUABLE_H
#define	VALUABLE_H

template <class T> 
class Valuable{
public:
    virtual T getValue()=0;
    virtual ~Valuable(){}
};
#endif	/* VALUABLE_H */

