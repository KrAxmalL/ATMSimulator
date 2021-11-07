#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class Transaction {
private:
	int transactionId;
	tm date;
	double sum;
	int cardFromId;
	int cardToId;

public:
	int getTransactionId() const { return transactionId; };
	void setTransactionId(const int newTransactionId) { transactionId = newTransactionId; };

	const tm& getTransactionDate() const { return date; };
	void setTransactionDate(const tm& newDate) { date = newDate; };

	double getSum() const { return sum; }
	void setSum(const double newSum) { sum = newSum; };

	int getCardFromId() const { return cardFromId; };
	void setCardFromId(const int newCardFromId) { cardFromId = newCardFromId; };

	int getCardToId() const { return cardToId; };
	void setCardToId(const int newCardToId) { cardToId = newCardToId; };
};