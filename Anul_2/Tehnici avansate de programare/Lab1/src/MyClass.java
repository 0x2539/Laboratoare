import java.util.Scanner;

/**
 * Created by Alexandru on 09-Oct-14.
 */
public class MyClass {

	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in);

//		System.out.print("tell me x = ");
//		int x = scanner.nextInt();
//		getDiv(x);

//		System.out.print("tell me a = ");
//		int a = scanner.nextInt();
//		System.out.print("tell me b = ");
//		int b = scanner.nextInt();
//		System.out.print("tell me c = ");
//		int c = scanner.nextInt();
//		ecuatie(a, b , c);

//		minMax(scanner);
		palindrom(scanner);
	}

	static int[] getDiv(int nr)
	{
		int[] divizori = new int[100];
		int nrDiv = 0;
		int diviz = 1;
		int sum = 0;

		while(nr > 1)
		{
			if(nr % diviz == 0 && diviz != 1)
			{
				nr /= diviz;
			}
			else
			{
				diviz++;

				while(nr % diviz != 0)
				{
					diviz++;
				}
				divizori[nrDiv] = diviz;
				nrDiv++;
				sum += diviz;
			}

		}

		System.out.println(sum);

		return divizori;
	}


	static void ecuatie(int a, int b, int c)
	{
		double delta = b * b - 4 * a * c;
		double r1, r2;

		if(delta >= 0)
		{
			r1 = (-b  + Math.sqrt(delta)) / (2 * a);
			r2 = (-b  - Math.sqrt(delta)) / (2 * a);

			System.out.println("Radacinile sunt: " + r1 + " " + r2);
		}
		else
		{
			System.out.println("Radacinile sunt: NA NA");
		}

	}

	static void minMax(Scanner sc)
	{
		System.out.print("Numarul de elemente: ");
		int n  = sc.nextInt();
		int x = 0;
		int min = 1000000, max = -1000000;

		for(int i = 0 ; i < n ; i++)
		{
			x = sc.nextInt();

			if(x < min)
			{
				min = x;
			}

			if(x > max)
			{
				max = x;
			}
		}

		System.out.println("Minim: " + min);
		System.out.println("Maxim: " + max);
	}

	static void palindrom(Scanner sc)
	{
		System.out.print("Elementul: ");
		String element = sc.next();

		for(int i = 0; i < element.length() / 2; i++)
		{
			if(element.charAt(i) != element.charAt(element.length() - i - 1))
			{
				System.out.println("Elementul: " + element + " nu este palindrom");
				return;
			}
		}

		System.out.println("Elementul: " + element + " este palindrom");
	}
}
