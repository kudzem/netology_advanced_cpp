#include <iostream>
#include <variant>
#include <optional>
#include <vector>
#include <ctime>
#include <algorithm>

std::variant<int, std::string, std::vector<int>> get_variant() {
	std::srand(std::time(nullptr));
	int random_variable = std::rand() % 3;

	std::variant<int, std::string, std::vector<int>> result;
	switch (random_variable)
	{
	case 0:
		result = 5;
		break;
	case 1:
		result = "string";
		break;
	case 2:
		result = std::vector<int>{ 1, 2, 3, 4, 5 };
		break;
	default:
		break;
	}
	return result;
}

std::optional<int> get_num_or_null(bool set) {
	if (set) return 10;
	return std::nullopt;
}

int main()
{
	auto opt_value = get_num_or_null(false);
	std::cout << opt_value.value_or(0) << std::endl;

	auto my_var = get_variant();

	if (std::holds_alternative<int>(my_var)) {
		std::cout << 2 * std::get<int>(my_var) << std::endl;
		return 0;
	}

	if (std::holds_alternative<std::string>(my_var)) {
		std::cout << std::get<std::string>(my_var) << std::endl;
		return 0;
	}

	auto v = std::get_if<std::vector<int>>(&my_var);
	if (!v)
	{
		return 1;
	}

	std::for_each(v->begin(),
		          v->end(),
		          [](const int& v) { std::cout << v << '\t'; });

	return 0;
}