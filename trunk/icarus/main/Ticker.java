package main;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class Ticker implements Runnable {
	private int interval;

	private boolean keepGoing;

	private MulticastSocket socket;

	private InetAddress group;

	private DatagramPacket packet;

	private final String MESSAGE = "TICK";

	public int getInterval() {
		return interval;
	}

	public void setInterval(int interval) {
		this.interval = interval;
	}

	public synchronized boolean isKeepGoing() {
		return keepGoing;
	}

	public synchronized void setKeepGoing(boolean keepGoing) {
		this.keepGoing = keepGoing;
	}

	public Ticker(int interval) {
		this.interval = interval;
		keepGoing = true;
		try {
			socket = new MulticastSocket(1237);
			group = InetAddress.getByName("239.239.239.239");
			socket.joinGroup(group);
		} catch (IOException e) {
			e.printStackTrace();
		}

		packet = new DatagramPacket(MESSAGE.getBytes(), MESSAGE.length(),
				group, 1237);
	}

	/**
	 * While the Ticker is active it will fire a timer tick then sleep for a set
	 * amount of time
	 */
	public void run() {
		while (isKeepGoing()) {
			fireTimerTick();
			sleepFor(interval);
		}
	}

	public void fireTimerTick() {
		try {
			socket.send(packet);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void sleepFor(int interval) {
		try {
			Thread.sleep(interval);
		} catch (InterruptedException e) {
		}
	}
}
