#include <iostream>
#include <Eigen/Dense>

using namespace std;

class LinearRegression
{
    public:

        LinearRegression();
        ~LinearRegression();

        void train(Eigen::VectorXd x_, Eigen::VectorXd y_, Eigen::VectorXd sigma_);

        double intercept();
        double slope();
        double chi2();

        double x_mean();
        double y_mean();
        double x_std();
        double y_std();

        double R2();
        double rvalue();

        // TODO
        // intercept error
        // slope error

    private:
        int n;
        Eigen::VectorXd x;
        Eigen::VectorXd y;
        Eigen::VectorXd sigma;
};
