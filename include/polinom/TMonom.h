#pragma once
using namespace std;
struct TMonom
{
	double coef; // êîýôôèöèåíò ìîíîìà
	int index; // èíäåêñ (ñâåðòêà ñòåïåíåé)


	TMonom() {
		coef = 0;
		index = 0;
	}

	TMonom(double co, int degX, int degY, int degZ) {
		index = degX * 100 + degY * 10 + degZ;
		coef = co;
	}

	void SetCoef(double cval) {
		coef = cval;
	}
	double GetCoef(void) {
		return coef;
	}
	void SetIndex(int ival) {
		index = ival;
	}
	int GetIndex(void) { return index; }


	bool operator==(const TMonom& other) {
		if ((other.coef == this->coef) && (other.index == this->index)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator>(const TMonom& other) {
		if ((other.coef > this->coef) && (other.index > this->index)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator<(const TMonom& other) {
		if ((other.coef < this->coef) && (other.index < this->index)) {
			return true;
		}
		else {
			return false;
		}
	}


};