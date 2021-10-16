#pragma once
#include <iostream>
#include <ctime>
using namespace std;

class Transaction {
private:
	int transactionId;
	tm date;
	unsigned sum;
	int cardFromId;
	int cardToId;

public:
	int getTransactionId() const { return transactionId; };
	void setTransactionId(const int newTransactionId) { transactionId = newTransactionId; };

	const tm& getTransactionDate() const { return date; };
	void setTransactionDate(const tm& newDate) { date = newDate; };

	unsigned getSum() const { return sum; }
	void setSum(const unsigned newSum) { sum = newSum; };

	int getCardFromId() const { return cardFromId; };
	void setCardFromId(const int newCardFromId) { cardFromId = newCardFromId; };

	int getCardToId() const { return cardToId; };
	void setCardToId(const int newCardToId) { cardToId = newCardToId; };
};