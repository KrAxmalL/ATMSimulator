#ifndef TRANSACTIONSLISTVIEW_H
#define TRANSACTIONSLISTVIEW_H


#include <iostream> 
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <string>

#include "Transaction.h"
#include "TextArea.h"

using namespace sf;
using std::vector;
using std::string;

using transactionIter = typename vector<Transaction>::const_iterator;


class TransactionsListView : public Drawable 
{
private:
	// vector<Transaction> transactionsList;
	vector<Text*> transactionsListTextAreas;
	bool _isVisible;


	void setPositions() {
		size_t i = 0;
		for (Text* nextTransactionText : transactionsListTextAreas) {
			float nextHeight = i * 50 + 120;
			nextTransactionText->setPosition({ 280,nextHeight });
			++i;
		}
	}
public:
	TransactionsListView() {}

	TransactionsListView(const vector<Transaction>& transactionsList, const int activeCardId) :
		TransactionsListView(transactionsList.begin(), transactionsList.end(), activeCardId)
	{}

	TransactionsListView(transactionIter first, transactionIter last, const int activeCardId)
		: _isVisible(false)
	{
		const float scale = 0.6f;

		Text* header = new Text();
		// todo: use fill
		std::stringstream headerStream;
		headerStream << std::left << setw(15) << "Card"
			<< setw(27) << "Sum"
			<< setw(19) << "Date";
		header->setString(headerStream.str());
		header->setFont(Assets::Instance().arial);
		header->setScale(scale, scale);

		transactionsListTextAreas.push_back(header);

		size_t i = 0;
		for (transactionIter transactionIter = first; transactionIter != last && i < 7; transactionIter++) {
			if (i > 6) {
				cerr << "To many transactions!" << endl;
			}

			std::stringstream sumstream;
			//if transaction from current card - show negative money amount
			//else - positive
			double sumToShow = transactionIter->getSum();
			int cardNumToShow = transactionIter->getCardFromId();
			if (transactionIter->getCardFromId() == activeCardId)
			{
				sumToShow = -sumToShow;
				cardNumToShow = transactionIter->getCardToId();
			}

			std::cout << "sum to show: " << sumToShow << std::endl;
			std::cout << "transactionFrom: " << transactionIter->getCardFromId() << std::endl;
			std::cout << "transactionTo: " << transactionIter->getCardToId() << std::endl;
			std::cout << "activeCardId: " << activeCardId << std::endl;

			sumstream << std::fixed << std::showpos << std::setprecision(2) << sumToShow;

			std::stringstream stream;
			stream << std::left << std::setw(14) << cardNumToShow
				<< std::setw(25) << sumstream.str()
				<< std::setw(19) << Transaction::dateToStr(*transactionIter);

			Text* nextTransactionArea = new Text();
			nextTransactionArea->setString(stream.str());
			nextTransactionArea->setFont(Assets::Instance().arial);
			nextTransactionArea->setScale(scale, scale);

			transactionsListTextAreas.push_back(nextTransactionArea);
			++i;
		}

		if (i == 0) {
			Text* noTransactionsHeader = new Text();
			noTransactionsHeader->setString("   No transactions to display");
			noTransactionsHeader->setFont(Assets::Instance().arial);
			noTransactionsHeader->setScale(scale, scale);
			transactionsListTextAreas.push_back(noTransactionsHeader);
		}

		setPositions();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		for (Text* area : transactionsListTextAreas) {
			target.draw(*area);
		}
	}

	void drawTo(sf::RenderWindow& window) {
		for (Text* area : transactionsListTextAreas) {
			window.draw(*area);
		}
	}

	void setVisible(bool isVisible) 
	{
		if (isVisible && !_isVisible) {
			setPositions();
		}
		else if (!isVisible && _isVisible) {
			for (Text* area : transactionsListTextAreas) {
				area->setPosition({ 100, 5000 });
			}
		}
		_isVisible = isVisible;
		
	}
};

#endif
