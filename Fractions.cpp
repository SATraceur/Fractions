//===================================================//
/* 
* File: Rational.cpp
* Author: Joshua Francis - 2147511 - fran0464

* Worklog
* 30/03/2016
* 12/04/2016
*/
//====================================================//

#include <iostream>

using namespace std;

class Rational {
public:
	int n_, d_;

	Rational();
	Rational(int n, int d); // default constructor declaration
	void positive_denominator_check();
	void lowest_terms();

	Rational(const Rational& other);
	Rational& operator=(const Rational& other);

	
private:
	int sum;
	int num1, num2;

};

int _abs(int v) { return v < 0 ? -v : v; }

Rational::Rational() {
	n_ = 0;
	d_ = 0;
}

Rational::Rational(int n, int d) {
	n_ = n;
	d_ = d;
}

Rational::Rational(const Rational& other) {
	n_ = other.n_;
	d_ = other.d_;
}

void Rational::positive_denominator_check() {
	if (d_ < 0) {
		d_ *= -1;
		n_ *= -1;
	}
}

void Rational::lowest_terms() {
	//n_ = _abs(n_);
	//d_ = _abs(d_);
	for (int i = 1; i < d_; i++) {
		if (n_%i == 0 && d_%i == 0) {
			n_ = n_ / i;
			d_ /= i;
			i = 1;
		}
	}
}

Rational& Rational::operator=(const Rational& other) {
	this->n_ = other.n_;
	this->d_ = other.d_;
	return *this;
}

ostream& operator<<(ostream& out, const Rational& r) {
	
	int n = r.n_, d = r.d_, whole_num = 0;
	cout << n << " n " << d << " d " << endl;

	while (n > d) { // CALCULATES WHOLE NUMBER.
		whole_num++; 
		n = n - d;
	}

	if (n == 0) {
		return out << 0;
	}
	else if (n % d == 0) { // if numerator is divisable by denominator, increment and output whole num.
		whole_num++;
		cout << "it got here ";
		if (n < 0) {
			return out << (whole_num * -1);
		}
		else {
			return out << whole_num;
		}
	}
	else if (whole_num > 0) {

		return out << whole_num << "," << n << '/' << d;
	}
	else if (n == d) {
		whole_num++;
		return out << whole_num;
	}
	else {
		return out << n << '/' << d;
	}

}

istream& operator>>(istream& in, Rational& r) {

	int n = 0, d = 1, whole_num = 0;

	if (in >> n && in.peek() == ',' && in.ignore()) {
		whole_num = n;
		if (whole_num > 0) {
			if (in >> n && in.peek() == '/' && in.ignore() && in >> d) {
				n = n + (d * whole_num);
				r = Rational(n, d);
			}
		}
		else if (whole_num < 0) {
			if (in >> n && in.peek() == '/' && in.ignore() && in >> d) {
				n = (d * whole_num) - n;
				r = Rational(n, d);
			}
		}
	} else if (in.peek() == '/' && in.ignore() && in >> d) {
		r = Rational(n, d); 
	} else { 
		r = Rational(n, 1); 
	}

	return in;
}

Rational operator+(const Rational& r1, const Rational& r2) {

	int numerator = r1.n_;
	int denominator = r1.d_;

	if (r1.d_ != r2.d_) {
		denominator = r1.d_ * r2.d_;
		numerator = (r1.n_ * r2.d_) + (r2.n_ * r1.d_);
	}
	else {
		numerator = r1.n_ + r2.n_;
	}

	Rational sum(numerator, denominator);
	sum.lowest_terms();
	sum.positive_denominator_check();

	return sum;
}

Rational operator-(const Rational& r1, const Rational& r2) {

	int numerator = r1.n_;
	int denominator = r1.d_;

	if (r1.d_ != r2.d_) {
		denominator = r1.d_ * r2.d_;
		numerator = (r1.n_ * r2.d_) - (r2.n_ * r1.d_);
	}
	else {
		numerator = r1.n_ - r2.n_;
	}

	Rational sum(numerator, denominator);
	sum.lowest_terms();
	sum.positive_denominator_check();

	return sum;  
}

Rational operator*(const Rational& r1, const Rational& r2) {
	
	int	denominator = r1.d_ * r2.d_;
	int	numerator = r1.n_ * r2.n_;

	Rational sum(numerator, denominator);
	sum.lowest_terms();
	sum.positive_denominator_check();

	return sum; 
}

Rational operator/(const Rational& r1, const Rational& r2) {

	int	denominator = r1.d_ * r2.n_;
	int	numerator = r1.n_ * r2.d_;

	Rational sum(numerator, denominator);
	sum.lowest_terms();
	sum.positive_denominator_check();

	return sum;
}


int main() {

	Rational n1, n2;
	char op;

	while (cin >> n1 >> op >> n2) {
		switch (op) {
		case '+': cout << n1 + n2 << endl; break;
		case '-': cout << n1 - n2 << endl; break;
		case '*': cout << n1 * n2 << endl; break;
		case '/': cout << n1 / n2 << endl; break;
		}
		//cout << n1 / n2 << " test." << endl;
	}
	system("pause");
	return(0);
}
