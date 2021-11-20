#pragma once
#include "CustomerRepository.h"
#include "CardService.h"

class CustomerService
{
private:

	CustomerRepository customerRepository;

	CardService& cardService;

	Customer* activeCustomer;

public:

	explicit CustomerService(CardService& cardService) : activeCustomer(nullptr), cardService(cardService), customerRepository{} {}

	~CustomerService()
	{
		delete activeCustomer;
	}

	void makeActiveCustomer()
	{
		delete activeCustomer;
		activeCustomer = new Customer(customerRepository.getCustomer(cardService.getActiveCard().getUId()));
	}

	const Customer& getActiveCustomer()
	{
		return *activeCustomer;
	}
};
