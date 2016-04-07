import java.util.*;

/**
 * Created by Alexandru on 16-Oct-14.
 */
public class MainClass {

	public static void main(String[] args)
	{
		Scanner scanner = new Scanner(System.in);

//		sortareVector(scanner);
//		eliminareDubluri(scanner);
//		citesteNume(scanner);
		checkForPalindrom(scanner);
	}

	private static int[] sortareVector(Scanner scanner)
	{
		System.out.print("Lungimea vectorului: ");
		int lungime = scanner.nextInt();

		int[] vector = new int[lungime];

		System.out.println("Elementele vectorului: ");
		for(int i = 0; i < lungime; i++)
		{
			vector[i] = scanner.nextInt();
		}

		for(int i = 0; i < lungime - 1; i++)
		{
			for(int j = i + 1; j < lungime; j++)
			{
				if(vector[i] > vector[j])
				{
					int aux = vector[i];
					vector[i] = vector[j];
					vector[j] = aux;
				}
			}
		}

		for(int i = 0; i < lungime; i++)
		{
			System.out.print(vector[i] + " ");
		}
		return vector;
	}

	private static void eliminareDubluri(Scanner scanner)
	{
		int[] vectorulMeu = sortareVector(scanner);
		int[] alDoileVector = new int[vectorulMeu.length];
		int n = 0;
		alDoileVector[n++] = vectorulMeu[0];

		for(int i = 1; i < vectorulMeu.length; i++)
		{
			if(vectorulMeu[i] != vectorulMeu[i-1])
			{
				alDoileVector[n++] = vectorulMeu[i];
			}
		}

		System.out.println();
		for(int i = 0; i < n; i++)
		{
			System.out.print(alDoileVector[i] + " ");
		}
	}


	private static List<String> citesteNume(Scanner scanner)
	{
		System.out.print("Numarul de persoane: ");
		int numarPersoane = scanner.nextInt();

		List<String> persoane = new ArrayList<String>();

		System.out.println("Persoanele: ");
		for(int i = 0; i < numarPersoane; i++)
		{
			persoane.add(i, scanner.next());
		}

		for(int i = 0; i < numarPersoane - 1; i++)
		{
			for (int j = i + 1; j < numarPersoane; j++)
			{
				if(persoane.get(i).length() > persoane.get(j).length())
				{
					String aux = persoane.get(i);
					persoane.set(i, persoane.get(j));
					persoane.set(j, aux);
				}
			}
		}
		System.out.print(persoane);
		return persoane;
	}

	private static void checkForPalindrom(Scanner scanner)
	{
		List<String> persoane = citesteNume(scanner);

		System.out.println();
		for(int i = 0; i < persoane.size(); i++)
		{
			System.out.println(persoane.get(i) + ": " + isPalindrom(persoane.get(i)));
		}
	}

	private static boolean isPalindrom(String cuvant)
	{
		String nou = "";

		for(int i = cuvant.length() - 1; i >= 0; i--)
		{
			nou += cuvant.charAt(i);
		}

		if(cuvant.equals(nou))
		{
			return true;
		}
		return false;
	}

}
