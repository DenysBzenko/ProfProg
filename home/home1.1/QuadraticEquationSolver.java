import java.util.Scanner;

public class QuadraticEquationSolver {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        double a = readDouble(scanner, "Enter the  a");
        double b = readDouble(scanner, "Enter the  b");
        double c = readDouble(scanner, "Enter the  c");

        double[] roots = solveQuadraticEquation(a, b, c);
        if (roots != null) {
            if (roots[0] == roots[1]) {
                System.out.println("The equation has one  root: " + roots[0]);
            } else {
                System.out.println("The equation has two  roots: " + roots[0] + " and " + roots[1]);
            }
        } else {
            System.out.println("The equation hasn't  roots.");
        }

        scanner.close();
    }

    public static double readDouble(Scanner scanner, String prompt) {
        System.out.print(prompt + ": ");
        while (!scanner.hasNextDouble()) {
            System.out.println("Invalid value. Please try again.");
            System.out.print(prompt + ": ");
            scanner.next();
        }
        return scanner.nextDouble();
    }

    public static double[] solveQuadraticEquation(double a, double b, double c) {
        double determinant = b * b - 4 * a * c;

        if (determinant > 0) {
            double root1 = (-b + Math.sqrt(determinant)) / (2 * a);
            double root2 = (-b - Math.sqrt(determinant)) / (2 * a);
            return new double[]{root1, root2};
        } else if (determinant == 0) {
            double root = -b / (2 * a);
            return new double[]{root, root};
        } else {
            return null;
        }
    }
}
