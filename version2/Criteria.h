#ifndef CRITERIA_H
#define CRITERIA_H

#include "Song.h"

class Criteria {
	friend ostream& operator<<(ostream& ost, const Criteria& criteria);
	
	public:
	    virtual bool matches(const Song& song) const = 0;
        virtual void print(ostream& ost) const = 0;
};

class A_Criteria : virtual public Criteria {
	
	public:
        A_Criteria(const string& a);
	    virtual bool matches(const Song& song) const;
        virtual void print(ostream& ost) const;

    private:  
        string artist;
};

class C_Criteria : virtual public Criteria {
	
	public:
        C_Criteria(const string& c);
	    virtual bool matches(const Song& song) const;
        virtual void print(ostream& ost) const;

    private:  
        string category;
};

class AorC_Criteria : public A_Criteria, public C_Criteria {
	
	public:
	    AorC_Criteria(const string& a, const string& c);
	    virtual bool matches(const Song& song) const;
        virtual void print(ostream& ost) const;
};

#endif