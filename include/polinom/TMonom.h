#pragma once
struct TMonom
{
	int coef; // ����������� ������
	int index; // ������ (������� ��������)


	TMonom() {
		coef = 0;
		index = 0;
	}

	TMonom(int co, int degX, int degY, int degZ) {
		index = degX * 100 + degY * 10 + degZ;
		coef = co;
	}
	TMonom(int coef_, int index_) {
		index = index_;
		coef = coef_;
	}

	void SetCoef(int cval) {
		coef = cval;
	}
	int GetCoef() {
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