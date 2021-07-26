/**
 * This i use to calculates how much X amount increases in Y days, on a Z year(365 days) base interest rate
 *
 * This code is Copyright 2020 under the GNU General Public License
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <unistd.h>

typedef long double my_double_t;

#include "stake_bonus.h"

#define CONVERT_PROCENT2DECIMAL(x) ((x) * 0.01)
#define CONVERT_DECIMAL2PROCENT(x) ((x) * 100.0)

#define YEAR_DAYS 365.0

#define HEX_ANNUAL_INFLATION  3.69
#define HEX_MAX_STAKE_DAYS 5555

// This is the % I think will be reasonable as defult future stake level   ¯\_(ツ)_/¯
#define HEX_DEFULT_STAKING_LEVEL 20.0
#define HEX_DEFULT_INTEREST (CONVERT_PROCENT2DECIMAL(HEX_ANNUAL_INFLATION) / CONVERT_PROCENT2DECIMAL(HEX_DEFULT_STAKING_LEVEL))

int opt_verbose = 0;
bool opt_use_hex_bounus = true;
bool opt_use_hex_increase = true;

using namespace std;


static void print_help(const char *s = nullptr)
{
	cerr << " Count the percentage growth. The arg are:" << endl
		<< " arg1  Number of days to stake." << endl
		<< " arg2  Value amount. You can use T M B (or t m b) as thousand, million and billion. All , and ' will be removed" << endl
		<< "Settings opt:" << endl
		<< " -p  Percentage /year  Default is: " << CONVERT_DECIMAL2PROCENT(HEX_DEFULT_INTEREST)
		<< "  That is based on that " << HEX_DEFULT_STAKING_LEVEL << " % of all Hex are staked" << endl
		<< " -t  The total Hex amont. Used to calculate the percentages, both this and -l must be used" << endl
		<< " -l  The lock  Hex amont. Used to calculate the percentages, both this and -t must be used" << endl
		<< " -n  Do NOT calculate with the Hex bonus" << endl
		<< " -i  Do NOT calculate with the Hex increase inflation by " << HEX_ANNUAL_INFLATION << " %" << endl
		<< " -v  Verbose = print more, can use twice for even more info" << endl
		<< " -h  This help" << endl
		<< endl
		<< "And of course these are just guesses!" << endl
		<< "Even with a perfect calculation, there is much else that affects the \"interest rate\" in Hex" << endl;

	if(s)
		cerr << "ERROR: " << s << endl;
}

static void print_help_exit(const char *s = nullptr)
{
	print_help(s);
	exit(0);
}

static void add_number_separator(string &text)
{
	size_t pos = 0;
	for (; pos < text.size() && '.' != text[pos]; ++pos);

	for (int i = 0; pos ; --pos, ++i)
	{
		if(i && i%3 == 0)
			text.replace(pos, 0, string(","));
	}
}

static string add_number_separator(my_double_t value)
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
		{ "b", "000000000" },
		{ "M", "000000" },
		{ "m", "000000" },
		{ "T", "000" },
		{ "t", "000" },
		{ ",", "" },
		{ "'", "" },
	};

	for (const Convert &a : conv)
		replace_string(value, a.from, a.to);
}


class percentCalculation
{
public:
	percentCalculation() = delete;

	percentCalculation(uint days, my_double_t amount, my_double_t percent)
	: m_amount(amount)
	, m_percent(percent)
	, m_days(days)
	{ }

	/**
	 * 1,2^(1.0/365.0)
	 * 10000×1,000499…^365
	 */
	inline my_double_t getCountPercent(int counts = 1) const
	{
		return pow(1.0 + m_percent, static_cast<my_double_t>(counts) / YEAR_DAYS);
	}

	my_double_t getCompoundInterest() const
	{
		const my_double_t hex_bonus = getHexBonus();
		const my_double_t calculated_amount_base = (getCountPercent(m_days) * (m_amount + hex_bonus));
		return calculated_amount_base - hex_bonus;
	}

	my_double_t getHexBonus() const
	{
		static bool print_bonus = true;
		my_double_t hex_bonus = 0.0;
		if(opt_use_hex_bounus)
		{
			hex_bonus = stakeStartBonusHex(m_amount, m_days);
			if(opt_verbose && print_bonus) {
				cout << std::fixed << "Bounus Hex added: " << add_number_separator(hex_bonus) << "    Use stacke amount " << add_number_separator(m_amount + hex_bonus) << endl;
				print_bonus = false;
			}
		}
		return hex_bonus;
	}

	/*
	 * See the comment in function _dailyRoundCalc() in the Hex contract
	 * https://etherscan.io/address/0x2b591e99afe9f32eaa6214f7b7629768c40eeb39#code
	 */
	my_double_t getDailyInterestRate(my_double_t interest) const
	{
		return exp(log(1.0 + interest) / 364.0) - 1.0;
	}

	my_double_t getNewAmount() const
	{
		const my_double_t hex_bonus = getHexBonus();
		const my_double_t hexDailyInterestRate = getDailyInterestRate(0.0369) + 1.0;
		const my_double_t procent_per_dag = getDailyInterestRate(m_percent);
		my_double_t calculated_amount = m_amount + hex_bonus;
		my_double_t calculated_amount_daily_increase = calculated_amount;

		for (uint loop_days = 1; loop_days <= m_days; ++loop_days) {
			calculated_amount += calculated_amount_daily_increase * procent_per_dag;
			if(opt_use_hex_increase)
				calculated_amount_daily_increase *= hexDailyInterestRate;
		}

		return calculated_amount - hex_bonus;
	}

private:
	const my_double_t m_amount;
	const my_double_t m_percent;
	const uint m_days;
};


static void run(int argc, char *argv[])
{
	int option_char, days = 0;
	my_double_t amount = 10000;
	my_double_t percentage = HEX_DEFULT_INTEREST;
	my_double_t hex_total = 0.0, hex_lock = 0.0;

	while((option_char = getopt(argc,argv,"ht:l:p:vni")) != -1)
	{
		switch(option_char)
		{
		case 'h':
			print_help_exit();
		break;

		case 't':
			hex_total = stod(optarg);
		break;

		case 'l':
			hex_lock = stod(optarg);
		break;

		case 'p':
			percentage = CONVERT_PROCENT2DECIMAL(stod(optarg));
		break;

		case 'v':
			opt_verbose++;
		break;

		case 'n':
			opt_use_hex_bounus = false;
		break;

		case 'i':
			opt_use_hex_increase = false;
		break;

		default:
			print_help_exit("Unknown option detected!\n");
		}
	}

	int arg_count = optind;

	if(HEX_DEFULT_INTEREST == percentage && hex_total && hex_lock) {
		if(hex_lock > hex_total)
			print_help_exit("Wrong total Hex  lock > total");
		percentage = CONVERT_PROCENT2DECIMAL(HEX_ANNUAL_INFLATION) / (hex_lock / hex_total);
		if(opt_verbose > 1) {
			cout << "Total Hex amont: " << setw(16) << add_number_separator(hex_total) << endl;
			cout << "Lock  Hex amont: " << setw(16) << add_number_separator(hex_lock) << endl;
		}
		if(opt_verbose)
			cout << "The amount of Hex staket: " << CONVERT_DECIMAL2PROCENT(hex_lock / hex_total) << " %   Calculate yearly \"interest\": " << CONVERT_DECIMAL2PROCENT(percentage) << " %" << endl;
	}

	if(arg_count >= argc) {
		print_help_exit("No arg");
	}

	days = stoi(argv[arg_count]);
	if(days < 1) {
		print_help_exit("You have staked < 1 days");
	}
	if(opt_use_hex_bounus && days > HEX_MAX_STAKE_DAYS) {
		cout << "Warning: You can't stack more than " << HEX_MAX_STAKE_DAYS
		<< " days in hex.  " << days << " days is too much. Changed to " << HEX_MAX_STAKE_DAYS << endl;
		days = HEX_MAX_STAKE_DAYS;
	}

	++arg_count;
	if(argc > arg_count) {
		string value(argv[arg_count]);
		convert_value_str(value);
		amount = stod(value);
	}


	percentCalculation calculat(days, amount, percentage);
	my_double_t new_amount = calculat.getNewAmount();

	cout << std::fixed << "Stake: " << add_number_separator(amount) << "  for days " << days;
	cout << std::setprecision(1) << " (" << days / YEAR_DAYS << " years)  should have increased to: " << add_number_separator(new_amount) << "  Hex" << endl;
	if(opt_verbose)
		cout << "The diffrens is " << add_number_separator(new_amount - amount) << "  or " << std::setprecision(3) << CONVERT_DECIMAL2PROCENT((new_amount / amount) - 1.0) << " %" << endl;
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
