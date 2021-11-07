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

	Transaction() {}
	Transaction(int _id): transactionId(_id) { }

	Transaction(int _transactionId, tm _date, double _sum, int _cardFromId, int _cardToId) :
		transactionId(_transactionId), date(_date), sum(_sum), 
		cardFromId(_cardFromId), cardToId(_cardToId)
	{

	}

	int getId() const { return transactionId; };
	void setId(const int newTransactionId) { transactionId = newTransactionId; };

	const tm& getTransactionDate() const { return date; };
	void setTransactionDate(const tm& newDate) { date = newDate; };

	double getSum() const { return sum; }
	void setSum(const double newSum) { sum = newSum; };

	int getCardFromId() const { return cardFromId; };
	void setCardFromId(const int newCardFromId) { cardFromId = newCardFromId; };

	int getCardToId() const { return cardToId; };
	void setCardToId(const int newCardToId) { cardToId = newCardToId; };
};

ostream& operator<<(ostream& os, const Transaction& t) 
{
	char buffer[20];
	strftime(buffer, 20, "%F %T", &t.getTransactionDate());

	return os << "id: " << t.getId() << "   date: " << buffer << "   sum: " << t.getSum() <<
		"   from: " << t.getCardFromId() << "   to: " << t.getCardToId();
}