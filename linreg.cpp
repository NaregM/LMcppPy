#include "linreg.hpp"

LinearRegression::LinearRegression(){}
LinearRegression::~LinearRegression(){}

void LinearRegression::train(Eigen::VectorXd x_, Eigen::VectorXd y_, Eigen::VectorXd sigma_)
{
    n = x_.size();
    x = x_;
    y = y_;
    sigma = sigma_;
}

double LinearRegression::intercept()
{

    double s = 0.0, sx = 0.0, sy = 0.0, sxy = 0.0, sxx = 0.0;
    double sig2 = 0.0;

    for(int i = 0; i < n; ++i)
    {
        sig2 = 1.0/(sigma[i] * sigma[i]);
        s += sig2;
        sx += x[i] * sig2;
        sy += y[i] * sig2;
        sxx += x[i] * x[i] * sig2;
        sxy += x[i] * y[i] * sig2;
    }

    double a1;

    double denom = s * sxx - sx * sx;
    a1 = (sxx * sy - sx * sxy)/denom;

    return a1;
}

double LinearRegression::slope()
{

    double s = 0.0, sx = 0.0, sy = 0.0, sxy = 0.0, sxx = 0.0;
    double sig2 = 0.0;

    for(int i = 0; i < n; ++i)
    {
        sig2 = 1.0/(sigma[i] * sigma[i]);
        s += sig2;
        sx += x[i] * sig2;
        sy += y[i] * sig2;
        sxx += x[i] * x[i] * sig2;
        sxy += x[i] * y[i] * sig2;
    }

    double a2;

    double denom = s * sxx - sx * sx;
    a2 = (s * sxy - sx * sy)/denom;

    return a2;
}

double LinearRegression::chi2()
{
    double intercept_ = intercept();
    double slope_ = slope();

    Eigen::VectorXd Y(x.size());
    double chisqr = 0.0;

    for (int i = 0; i < x.size(); ++i)
    {
        Y[i] = intercept_ + slope_ * x[i];
        double delta = (y[i] - Y[i])/sigma[i];
        chisqr += delta * delta;
    }

    return chisqr;
}

double LinearRegression::x_mean()
{
    double xbar = 0.0;
    for (int i = 0; i < n; ++i)
    {
        xbar += x[i];
    }

    return xbar/double(n);
}

double LinearRegression::y_mean()
{
    double ybar = 0.0;
    for (int i = 0; i < n; ++i)
    {
        ybar += y[i];
    }

    return ybar/double(n);
}

double LinearRegression::R2()
{
    double SS_tot = 0.0;
    double SS_res = 0.0;
    double ybar = y_mean();

    for (int i = 0; i < n; ++i)
    {
        SS_tot += (y[i] - ybar) * (y[i] - ybar);
    }

    double intercept_ = intercept();
    double slope_ = slope();

    Eigen::VectorXd f(n);

    for (int i = 0; i < n; ++i)
    {
        f[i] = intercept_ + slope_ * x[i];
        SS_res += (y[i] - f[i]) * (y[i] - f[i]);
    }

    return 1.0 - SS_res/SS_tot;
}

double LinearRegression::rvalue()
{
    return pow(R2(), 0.5);
}

double LinearRegression::x_std()
{
    double sig_x = 0.0;
    double xbar = x_mean();
    for (int i = 0; i < n; ++i)
    {
        sig_x += (x[i] - xbar) * (x[i] - xbar);
    }

    return pow(sig_x/n, 0.5);
}

double LinearRegression::y_std()
{
    double sig_y = 0.0;
    double ybar = y_mean();
    for (int i = 0; i < n; ++i)
    {
        sig_y += (y[i] - ybar) * (y[i] - ybar);
    }

    return pow(sig_y/n, 0.5);
}
