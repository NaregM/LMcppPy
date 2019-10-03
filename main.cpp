#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <random>
#include "linreg.hpp"

using namespace std;

int main()
{
    // Generate random data from Normal distribution ==================================================================
    default_random_engine gen;
    gen.seed(420);

    double mu = 5.0;
    double sigma = 10;
    normal_distribution<double> Normal(mu, sigma);

    Eigen::VectorXd X = Eigen::VectorXd(60);
    Eigen::VectorXd Y = Eigen::VectorXd(60);

    for(int i = 0; i < X.size(); i++)
    {
        X[i] = double(i + 10);
    }

    for(int i = 0; i < X.size(); i++)
    {
        Y[i] = pow(X[i], 1.0) + Normal(gen);
    }

    // Save the generated data ======================================================================================
    ofstream myfile;
    myfile.open("data.txt");

    for (int i = 0; i < X.size(); ++i)
    {
        myfile << X[i] << ", ";
        myfile << Y[i] << endl;
    }

    myfile.close();

    Eigen::VectorXd SIGMA = Eigen::VectorXd::Ones(X.size());

    // ===============================================================================================================

    // Create an instant of LinearRegression
    LinearRegression lm;

    // Train the model
    lm.train(X, Y, SIGMA);

    cout << "Intercept = " << lm.intercept() << endl;
    cout << "Slope = " << lm.slope() << endl;
    cout << "Chi2 = " << lm.chi2() << endl;
    cout << "x_mean = " << lm.x_mean() << endl;
    cout << "x_std = " << lm.x_std() << endl;
    cout << "y_mean = " << lm.y_mean() << endl;
    cout << "y_std = " << lm.y_std() << endl;
    cout << "R-squared = " << lm.R2() << endl;
    cout << "r-value = " << lm.rvalue() << endl;

return 0;
}
