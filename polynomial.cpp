#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//

// Default constructor p(x) = 0
Polynomial::Polynomial()
{
	// ToDo
	capacity = 1;
	termArray = new Term[capacity];
	terms = 0;
}

// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
	// ToDo
	capacity = source.Capacity();
	terms = source.Terms();
	termArray = new Term[capacity];
	for (int i = 0; i < terms; i++) {
		termArray[i].coef = source.GetTerm(i).coef;
		termArray[i].exp = source.GetTerm(i).exp;
	}

}

// Destructor
Polynomial::~Polynomial()
{
	// ToDo
	delete[] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
	// ToDo
	capacity = source.Capacity();
	terms = source.Terms();
	delete[] termArray;
	termArray = new Term[capacity];
	for (int i = 0; i < terms; i++) {
		termArray[i].coef = source.GetTerm(i).coef;
		termArray[i].exp = source.GetTerm(i).exp;
	}
	return *this;
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
	Polynomial c;

	// ToDo
	int a = 0, b = 0;
	while ((a < terms) && (b < source.Terms())) {
		if (termArray[a].exp == source.GetTerm(b).exp) {
			float d = termArray[a].coef + source.GetTerm(b).coef;
			if (d != 0) c.CreateTerm(d, termArray[a].exp);
			a++; b++;
		}
		else if (termArray[a].exp > source.GetTerm(b).exp) {
			c.CreateTerm(termArray[a].coef, termArray[a].exp);
			a++;
		}
		else {
			c.CreateTerm(source.GetTerm(b).coef, source.GetTerm(b).exp);
			b++;
		}
	}

	for (; a < terms; a++) {
		c.CreateTerm(termArray[a].coef, termArray[a].exp);
	}
	for (; b < source.Terms(); b++) {
		c.CreateTerm(source.GetTerm(b).coef, source.GetTerm(b).exp);
	}

	return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
	Polynomial c;

	int a = 0, b = 0;
	while ((a < terms) && (b < source.Terms())) {
		if (termArray[a].exp == source.GetTerm(b).exp) {
			float d = termArray[a].coef - source.GetTerm(b).coef;
			if (d != 0) c.CreateTerm(d, termArray[a].exp);
			a++; b++;
		}
		else if (termArray[a].exp > source.GetTerm(b).exp) {
			c.CreateTerm(termArray[a].coef, termArray[a].exp);
			a++;
		}
		else {
			c.CreateTerm(-source.GetTerm(b).coef, source.GetTerm(b).exp);
			b++;
		}
	}

	for (; a < terms; a++) {
		c.CreateTerm(termArray[a].coef, termArray[a].exp);
	}
	for (; b < source.Terms(); b++) {
		c.CreateTerm(-source.GetTerm(b).coef, source.GetTerm(b).exp);
	}

	return c;

}


Polynomial Polynomial::operator * (const Polynomial& source)
{
	Polynomial c;

	// ToDo
	for (int i = 0; i < terms; i++) {
		Polynomial d;
		for (int j = 0; j < source.terms; j++) {
			d.CreateTerm(termArray[i].coef*source.termArray[j].coef, termArray[i].exp + source.termArray[j].exp);
		}
		c = c + d;
	}

	return c;
}


float Polynomial::Eval(float x)
{
	float ret = 0;

	// ToDo
	for (int i = 0; i < terms; i++) {
		ret += termArray[i].coef*pow(x, termArray[i].exp);
	}

	return ret;
}




// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
	Polynomial c;

	// ToDo
	for (int i = 0; i < terms - 1; i++) {
		c.CreateTerm(termArray[i].coef * termArray[i].exp, termArray[i].exp - 1);
	}
	if (termArray[terms - 1].exp != 0) {
		c.CreateTerm(termArray[terms - 1].coef * termArray[terms - 1].exp, termArray[terms - 1].exp - 1);
	}

	return c;

}


void Polynomial::CreateTerm(const float coef, const int exp)
{
	// ToDo
	if (exp < 0 || coef == 0) return;

	for (int j = 0; j < terms; j++) {
		if (termArray[j].exp == exp) {
			termArray[j].coef = coef;
			return;
		}
	}

	if (terms == capacity) {
		capacity *= 2;
		Term *temp = new Term[capacity];
		for (int k = 0; k < terms; k++) {
			temp[k] = termArray[k];
		}
		delete[] termArray;
		termArray = temp;
	}

	int i;
	for (i = 0; i < terms; i++) {
		if (termArray[i].exp < exp) {
			for (int j = i; j < terms; j++) {
				termArray[j + 1].exp = termArray[j].exp;
				termArray[j + 1].coef = termArray[j].coef;
			}
			break;
		}
	}
	termArray[i].exp = exp;
	termArray[i].coef = coef;
	terms++;
}

