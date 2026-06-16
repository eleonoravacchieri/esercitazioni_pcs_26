#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <vector>

double condA(const Eigen::MatrixXd& A){
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
    Eigen::VectorXd singularValuesA = svd.singularValues();
    return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}
struct risultati
{
    unsigned int it;
    Eigen::VectorXd x;
};

risultati gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, double res_tol, unsigned int it_max){

    unsigned int n = b.size(); 
    Eigen::VectorXd x = Eigen::VectorXd::Zero(n);
    Eigen::VectorXd res = b - A * x;
    Eigen::VectorXd p = res;
    double res_norm_0 = res.norm();

    unsigned int it=0;

    //iterazione
    while (it < it_max && res.norm()> res_tol * res_norm_0){
        const double alpha_k = res.dot(res) / (res.dot(A * p));
        x= x + alpha_k * p;
        res = b - A * x;
        double beta_k= p.dot(A * res)/ p.dot(A * p);
        p= res - beta_k * p;
        it++;
    }

    return {it, x};
}