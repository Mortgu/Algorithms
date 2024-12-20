import java.util.Scanner;
import java.util.Arrays;

public class Matrix {

    private int[][] matrix;
    public final int width, height;

    public Matrix(int width, int height) {
        this.width = width;
        this.height = height;
        this.matrix = new int[width][height];
    }

    /* Inititalize the matrix with 0. */
    public void init() {
        for (int h = 0; h < this.height; h++) {
            for (int w = 0; w < this.width; w++) {
                this.matrix[w][h] = 0;
            }
        }
    }

    public void print() {
        for (int h = 0; h < this.height; h++) {
            for (int w = 0; w < this.width; w++) {
                System.out.print(this.matrix[w][h] + " ");
            }
            System.out.println(" ");
        }
        System.out.println(" ");
    }

    public void input() {
        Scanner scanner = new Scanner(System.in);
        for (int h = 0; h < this.height; h++) {
            for (int w = 0; w < this.width; w++) {
                System.out.print("[" + w + "][" + h + "] > ");
                this.matrix[w][h] = Integer.parseInt(scanner.nextLine());
            }   
        }
    }

    public void random() {
        for (int h = 0; h < this.height; h++) {
            for (int w = 0; w < this.width; w++) {
                //Random random;
                //int number = random.nextInt((255 - (-255)) + 1) + (-255);
                int random = (-255) + (int)((Math.random() * (255 - (-255) + 1)));
                this.matrix[w][h] = random;
            }
        }
    }

    public void add(Matrix m) {
        if (this.width != m.width) {
            System.out.println("Error! Failed to perform addition!");
            return;
        }        

        for (int h = 0; h < this.height; h++) {
            for (int w = 0; w < this.width; w++) {
                this.matrix[w][h] = this.matrix[w][h] + m.matrix[w][h];
            }
        }
    } 

    public void multiply(Matrix m) {
        if (this.height != m.width || this.width != m.height) {
            System.out.println("Error! Matrix dimensions are not compatible!"); 
            return;
        }

        Matrix result = new Matrix(m.width, this.height);

        for (int w = 0; w < result.width; w++) {
            for (int h = 0; h < result.height; h++) {
                for (int k = 0; k < result.width; k++) {
                    result.matrix[w][h] += this.matrix[k][h] * m.matrix[w][h];
                }
            }   
        }
    }

    public int maximumSubtotal1d(int[] array) {
        int s, local = 0, global = Integer.MIN_VALUE;

        for (int i = 0; i < array.length; i++) {
            s = local + array[i];
            if (s > array[i]) local = s;
            else local = array[i];
            if (local > global) global = local; 
        }

        return global;
    }

    public int maximumSubtotal2d() {
        int rows = this.matrix.length, 
            cols = this.matrix[0].length;
        int global = Integer.MIN_VALUE; 

        int[] temp = new int[cols];

        for (int startRow = 0; startRow < rows; startRow++) {
            Arrays.fill(temp, 0);

            for (int endRow = startRow; endRow < rows; endRow++) {
                for (int col = 0; col < cols; col++) {
                    temp[col] += this.matrix[endRow][col];
                }

                int sum = maximumSubtotal1d(temp);
                global = Math.max(global, sum);
            }
        }

        return global;
    }

    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }

    public static void main(String[] args) {
        Matrix matrix = new Matrix(3, 2);
        matrix.random();
        matrix.print();

        int max = matrix.maximumSubtotal2d();

        System.out.println("max: " + max);
    }
}
