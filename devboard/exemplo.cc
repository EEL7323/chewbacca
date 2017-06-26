#include <iostream>
#include "restclient/restclient.h"
#include "jsonparser/json.hpp"

using json = nlohmann::json;

int main()
{	
	RestClient::Response r = RestClient::get("http://cluster.linse.ufsc.br:5000/transaction");
	//std::cout << r.body;
	auto j = json::parse(r.body);
	for (auto& element : j) 
	{
		json j2 = element;
		std::cout << j2["username"] << std::endl;
	}
	return 0;




}

