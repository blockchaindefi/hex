/**
 * This i use to calculates how much X amount increases in Y days, on a Z year(365 days) base interest rate
 *
 * This code is Copyright 2020 under the GNU General Public License
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>

#define HEX_BASE_PERCENT 0.08
using namespace std;

/**
 * 1,2^(1.0/365.0)
 * 10000×1,000499…^365
 */
class percentCalculation
{
public:
	explicit percentCalculation(double percent, double days = 365)
	: m_percent(percent)
	, m_days(days)
	{ }

	// 1,2^(1÷365)
	inline double getCountPercent(int counts = 1)
	{
		return pow(1.0 + m_percent, static_cast<double>(counts) / m_days);
	}

private:
	double m_percent;
	double m_days;
};

/**
 * This is a somewhat sloppy calculation of the increase of the percent depending on the amount
 *
 * To be scalable use:
 * bonus = (input * (min(input, 150e6)/1500e6)
 * From: https://medium.com/@jimmypomerleau/intro-d37b5b720487
 */
static double get_interest_from_amount(double amount)
{
	const double max_amount = std::min(amount,  150000000.0);
	const double bonus = amount * (max_amount / 1500000000.0);
	return (bonus / amount) + HEX_BASE_PERCENT;
}

static void add_number_separator(string &text)
{
	int pos = 0;
	for (; pos < text.size() && '.' != text[pos]; ++pos);

	for (int i = 0; pos ; --pos, ++i)
	{
		if(i && i%3 == 0)
			text.replace(pos, 0, string(","));
	}
}

static string add_number_separator(double value)
{
	stringstream stream;
	stream << std::fixed << std::setprecision(0) << value;
	string str(stream.str());
	add_number_separator(str);
	return str;
}


static void replace_string(string &text, const string& search, const string& replace)
{
	for (size_t pos = 0; (pos = text.find(search, pos)) != std::string::npos ;)
	{
		text.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

static void convert_value_str(string &value)
{
	static constexpr struct Convert
	{
		const char *from;
		const char *to;
	} conv[]= {
		{ "B", "000000000" },
		{ "M", "000000" },
		{ "T", "000" },
		{ ",", "" },
		{ "'", "" },
	};

	for (const Convert &a : conv)
		replace_string(value, a.from, a.to);
}

static void run(int argc, char *argv[])
{
	int days = 0;
	double amount = 10000;
	double percentage = HEX_BASE_PERCENT;
	int year_days = 365;

	if(argc <= 1 || string(argv[1]).find("h") != string::npos) {
		cerr << " Count the percentage growth. The arg are:" << endl
			<< " Number of days.  Or --help/-h for for this help" << endl
			<< " Value amount. Default value: " << amount << endl
			<< " Percentage /year. Default value: " << percentage << endl
			<< "  (There is otherwise a sloppy calculation of the increase of the percent depending on the amount added)" << endl
			<< " Year days used in the percent calculation. Default value: " << year_days << endl;
		if(argc <= 1)
			throw EXIT_FAILURE;
		throw EXIT_SUCCESS;
	}

	int arg_count = 1;
	days = stoi(argv[arg_count]);

	++arg_count;
	if(argc > arg_count) {
		string value(argv[arg_count]);
		convert_value_str(value);
		amount = stod(value);
	}

	percentage = get_interest_from_amount(amount);

	++arg_count;
	if(argc > arg_count) {
		percentage = stod(argv[arg_count]);
	}

	++arg_count;
	if(argc > arg_count)
		year_days = stoi(argv[arg_count]);

	percentCalculation calculat(percentage, year_days);

	double calculated_amount = calculat.getCountPercent(days) * amount;
	cout << "For interest for " << days << " days at " << percentage << " % compound, new  amount: " << setw(12) << std::fixed << std::setprecision(2)
		<< add_number_separator(calculated_amount) << "  difference: " << add_number_separator(calculated_amount - amount) << endl
		<< std::setprecision(4) << " Increase by " << ((calculated_amount / amount) - 1.0) * 100.0 << " %"
		<< "  (count back percent " << (1.0 -	(amount / calculated_amount)) * 100.0 << " %)" << endl;
}

int main(int argc, char *argv[])
{
	int main_ret = EXIT_FAILURE;
	try
	{
		run(argc, argv);
		main_ret = EXIT_SUCCESS;
	} catch (const exception &e) {
		cerr << "Catch error  \"" << e.what() << "\"  - Sanitize your argument list I guess..?" << endl;
		return EXIT_FAILURE;
	} catch (int e) {
		main_ret = e;
		if(EXIT_FAILURE == e)
			cerr << "Catch error  exit" << endl;
	} catch (...) {
		cerr << "Catch error  Unknown error..?" << endl;
	}
	return main_ret;
}
