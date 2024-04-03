#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} {
	}

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} {
	}

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:
	Mean() : m_sum{0}, m_count{0} {
	}

	void update(double next) override {
		m_sum += next;
		m_count++;
	}

	double eval() const override {
		return m_sum/m_count;
	}

	const char * name() const override {
		return "mean";
	}

private:
	double m_sum;
	int m_count;
};

class StD : public IStatistics {
public:
	StD() : m_sum{0}, m_count{0} {
	}

	void update(double next) override {
		m_v.push_back(next);
		m_sum += next;
		m_count++;
	}

	double eval() const override {
		double avg = m_sum/m_count;
		double tmpOtkl;
		std::vector<double> qotkl;
		for(auto it = m_v.begin(); it != m_v.end(); ++it) {
			qotkl.push_back((*it-avg)*(*it-avg));
		}

		double qotklSum = 0;
		for(auto it = qotkl.begin(); it != qotkl.end(); ++it) {
			qotklSum += *it;
		}
		double dispersia = qotklSum/qotkl.size();
		double stdOtkl = sqrt(dispersia);
		return stdOtkl;
	}

	const char * name() const override {
		return "StD";
	}

private:
	std::vector<double> m_v;
	double m_sum;
	int m_count;
};

int main() {

	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new StD{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}