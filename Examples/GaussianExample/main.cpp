// Evaluates 3D Gaussian at various spherical coordinates where 
// psi(x, y, z) = pi^{-3/2} * e^{-(x^2+y^2+z^2)}
// such that int_{-infty}^{infty} int_{-infty}^{infty} int_{-infty}^{infty} psi(x, y, z) dz dy dx = 1

#include <iostream> 

#include <expression_parser.hpp>
#include <expression_composer.hpp>
#include <expression_visualizer.hpp>

int main(int argc, char *argv[])
{
    try {
        std::shared_ptr<ConstantNode> pi(new ConstantNode(3.14159265358979323846));
        std::shared_ptr<ConstantNode> e(new ConstantNode(2.71828182845904523536));
        std::shared_ptr<VariableNode> x(new VariableNode(0.0));
        std::shared_ptr<VariableNode> y(new VariableNode(0.0));
        std::shared_ptr<VariableNode> z(new VariableNode(0.0));

        std::map<std::string, std::shared_ptr<Node>> node_map = { { "pi", pi }, { "e", e }, { "x", x }, { "y", y }, { "z", z } };

        ExpressionParser expression_parser("pi ^ \\left{ -3 / 2 \\right} * e ^ \\left{ - \\left( x ^ 2 + y ^ 2 + z ^ 2 \\right) \\right}", node_map);
        
        std::shared_ptr<Node> psi = expression_parser.Parse();

        for (double rho = 0.0; rho < 2.0; rho += 0.5) {
            for (double theta = 0.0; theta < 3.14159; theta += 0.5 * 3.14159) {
                for (double phi = 0.0; phi < 2.0 * 3.14159; phi += 0.5 * 3.14159) {
                    *x = rho * std::sin(theta) * std::cos(phi);
                    *y = rho * std::sin(theta) * std::sin(phi);
                    *z = rho * std::cos(theta);

                    std::cout << "psi(" << rho << ", " << theta << ", " << phi << ") = " << psi << std::endl << std::endl;
                }
            }
        }

        std::cout << "Visualized expression tree: " << std::endl;
        std::cout << ExpressionVisualizer(psi, node_map) << std::endl << std::endl;

        std::cout << "Re-composed expression from expression tree: " << std::endl;
        std::cout << ExpressionComposer(psi, node_map) << std::endl << std::endl;
    }
    catch(std::exception const &exception) {
        std::cout << exception.what() << std::endl;
        
        return 1;
    }

    return 0;
}