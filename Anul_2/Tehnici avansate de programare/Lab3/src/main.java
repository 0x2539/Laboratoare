import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**
 * Created by Alexandru on 30-Oct-14.
 */
public class main {

	public static void main(String[] args)
	{
		//seturi();
		problema();
	}

	public static void seturi()
	{
		Set<String> set = new HashSet<String>();

		Collections.addAll(set, "d", "e");
		set.add("C");
		set.add("B");
		set.add("A");

		Iterator it = set.iterator();

		while(it.hasNext())
		{
			System.out.println(it.next());
		}
	}

	static Set<Luna> luni = new HashSet<Luna>();
	public static void problema()
	{
		luni.add(addLunaCuEvenimente("luna1", new String[] {"paste", "craciun"}));
		luni.add(addLunaCuEvenimente("luna2", new String[] {"paste2", "craciun2", "craciun3"}));

		printAll();
		removeEvent("luna2", "craciun2");

		System.out.println(getLunaCuEveniment("craci"));
		System.out.println("Dupa stergere:");
		printAll();
	}

	public static void removeEvent(String name, String event)
	{
		Iterator it = luni.iterator();

		while(it.hasNext()) {
			Luna luna = (Luna) it.next();
			if(luna.nume.equals(name))
			{
				luna.removeEvent(event);
			}
		}
	}

	public static boolean hasEvent(String name, String event)
	{
		Iterator it = luni.iterator();

		while(it.hasNext()) {
			Luna luna = (Luna) it.next();
			if(luna.nume.equals(name))
			{
				return luna.hasEvent(event);
			}
		}
		return false;
	}

	public static void addEvent(String name, String event)
	{
		Iterator it = luni.iterator();

		while(it.hasNext()) {
			Luna luna = (Luna) it.next();
			if(luna.nume.equals(name))
			{
				luna.addEvent(event);
			}
		}
	}

	public static void replaceEvent(String name, String event1, String event2)
	{
		Iterator it = luni.iterator();

		while(it.hasNext()) {
			Luna luna = (Luna) it.next();
			if(luna.nume.equals(name))
			{
				luna.replaceEvent(event1, event2);
			}
		}
	}

	public static void printAll()
	{
		Iterator it = luni.iterator();

		while(it.hasNext())
		{
			Luna luna = (Luna)it.next();
			System.out.print(luna.nume + ": ");
			luna.printAll();
			System.out.println();
		}
	}

	public static Luna addLunaCuEvenimente(String nume, String[] events)
	{
		Luna luna = new Luna(nume);
		for(int i = 0; i < events.length; i++)
		{
			luna.addEvent(events[i]);
		}
		return luna;
	}

	public static String getLunaCuEveniment(String eveniment)
	{
		Iterator it = luni.iterator();

		while(it.hasNext())
		{
			Luna luna = (Luna)it.next();
			if(luna.hasEvent(eveniment))
			{
				return luna.nume;
			}
		}
		return "''";
	}

	public static String lunaCuCeleMaiMulteEvenimente()
	{
		Iterator it = luni.iterator();
		int maxim  = 0;
		String nume = "";

		while(it.hasNext())
		{
			Luna luna = (Luna)it.next();
			if(luna.getEventsCount() > maxim)
			{
				maxim = luna.getEventsCount();
				nume = luna.nume;
			}
		}
		return nume + " " + maxim;
	}

	public static String lunaCuCeleMaiPutineEvenimente()
	{
		Iterator it = luni.iterator();
		int minim  = 1000000;
		String nume = "";

		while(it.hasNext())
		{
			Luna luna = (Luna)it.next();
			if(luna.getEventsCount() < minim)
			{
				minim = luna.getEventsCount();
				nume = luna.nume;
			}
		}
		return nume + " " + minim;
	}

	//Pentru fiecare luna a anului sa se citeasca un set de evenimente (Paste, Craciun, etc.)
	//Adaugare, modificare, stergere pentru o anumita luna
	//Cautarea unui eveniment
	//luna cu numarul maxim/minim de evenimente
}


class Luna
{
	String nume;
	Set<String> events = new HashSet<String>();

	public Luna(String nume)
	{
		this.nume = nume;
	}

	public void addEvent(String event)
	{
		if(!events.contains(event))
		{
			events.add(event);
		}
		else
		{
			System.err.println("ADD: Evenimentul: " + event + " deja exista");
		}
	}

	public void removeEvent(String event)
	{
		try {
			events.remove(event);
		}
		catch (Exception ex) {
			System.err.println("REMOVE: Evenimentul: " + event + " nu exista");
		}
	}

	public void replaceEvent(String oldEvent, String newEvent)
	{
		if(events.contains(oldEvent))
		{
			events.remove(oldEvent);
			events.add(newEvent);
		}
		else
		{
			System.err.println("REPLACE: Evenimentul: " + oldEvent + " nu exista");
		}
	}

	public boolean hasEvent(String event)
	{
		return events.contains(event);
	}

	public int getEventsCount()
	{
		return events.size();
	}

	public void printAll()
	{
		Iterator it = events.iterator();

		while(it.hasNext())
		{
			System.out.print(it.next() + " ");
		}
	}
}