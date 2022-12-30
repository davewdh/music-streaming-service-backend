#include "Criteria.h"

//A_Criteria
A_Criteria::A_Criteria(const string& a) : artist(a) {
}

//returns true if the Song::category matches the artist member
bool A_Criteria::matches(const Song& song) const {
    return this->artist == song.getArtist();
}

void A_Criteria::print(ostream& ost) const {
    ost << "This Criteria will match a Song by the artist: " << this->artist << endl;
}

//C_Criteria
C_Criteria::C_Criteria(const string& c) : category(c) {
}

//returns true if the Song::category matches the category member
bool C_Criteria::matches(const Song& song) const {
    return this->category == song.getCategory();
}

void C_Criteria::print(ostream& ost) const {
    ost << "This Criteria will match a Song by the category: " << this->category << endl;
}

//AorC_Criteria
AorC_Criteria::AorC_Criteria(const string& a, const string& c) : A_Criteria(a), C_Criteria(c) {

}

//returns true if the Song::category matches the category member or the Song::artist matches the artist member
bool AorC_Criteria::matches(const Song& song) const {
    return A_Criteria::matches(song) || C_Criteria::matches(song);
}

void AorC_Criteria::print(ostream& ost) const {
    A_Criteria::print(ost);
    C_Criteria::print(ost);
}

ostream& operator<<(ostream& ost, const Criteria& criteria){
    criteria.print(ost);
    return ost;
}