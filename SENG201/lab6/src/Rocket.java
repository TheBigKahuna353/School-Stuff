

import javax.swing.*;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

/**
 * Class that models a rocket.
 */
public class Rocket {

	/**
	 * Property that can be listened to to find out when a mission has completed. Use {@link #onMission()}
	 * to check mission status.
	 */
	public static final String MISSION_COMPLETE = "missionComplete";

	/**
	 * Property that can be listened to for changes in rocket status.
	 */
	public static final String ROCKET_STATUS = "rocketStatus";

	/**
	 * Property that can be listened to for changes in mission progress.
	 */
	public static final String MISSION_PROGRESS = "missionProgress";

	// The frequency of mission progress updates in milliseconds
	private static final int MISSION_PROGRESS_DELAY_MS = 250;

	// Used to report property change events to our listeners
	private final PropertyChangeSupport pcs;

	// Swing timer used for timing rocket missions. Calls {@link #onMissionComplete} on the
	// Swing event dispatching thread (EDT) when the time is up
	private final Timer timer = new Timer(MISSION_PROGRESS_DELAY_MS, (event) -> onMissionProgress());

	// The name of this rocket
	private final String name;

	// The current fuel level of this rocket
	private FuelLevel fuel;

	// The current cleanliness status of this rocket
	private Cleanliness cleanliness;

	// The number of missions completed by this rocket
	private int missionsCompleted = 0;
	private int missionProgressPercent;

	/**
	 * Represents the fuel level of a {@link Rocket}
	 */
	public enum FuelLevel {
		EMPTY("Empty"),
		LOW("Low"),
		FULL("Full");

		/**
		 * A user friendly description of the value of this enum
		 */
		public final String value;
		
		FuelLevel(String value) {
			this.value = value;
		}
	}

	/**
	 * Represents how clean a {@link Rocket} is
	 */
	public enum Cleanliness {
		CLEAN("Clean"),
		DIRTY("Dirty");

		/**
		 * A user friendly description of the value of this enum
		 */
		public final String value;
		
		Cleanliness(String value) {
			this.value = value;
		}
	}

	/**
	 * Creates a clean, fully fueled rocket with the given name.
	 *
	 * @param name The name for the rocket
	 */
	public Rocket(String name) {
		this.name = name;
		fuel = FuelLevel.FULL;
		cleanliness = Cleanliness.CLEAN;
		timer.setRepeats(true);
		timer.setDelay(MISSION_PROGRESS_DELAY_MS);
		pcs = new PropertyChangeSupport(this);
	}

	/**
	 * Adds a property change listener to this Rocket. The listener will be informed
	 * when this Rocket's status changes. See {@link #ROCKET_STATUS}, {@link #MISSION_COMPLETE}.
	 *
	 * @param listener The listener to report property updates to
	 */
	public void addListener(PropertyChangeListener listener) {
		pcs.addPropertyChangeListener(listener);
	}

	/**
	 * Removes a previously added property change listener to this Rocket.
	 *
	 * @param listener The listener to remove
	 */
	public void removeListener(PropertyChangeListener listener) {
		pcs.removePropertyChangeListener(listener);
	}

	/**
	 * Gets the name of this Rocket.
	 *
	 * @return The name of this rocket
	 */
	public String getName() {
		return name;
	}

	/**
	 * Gets the current fuel level of this Rocket.
	 *
	 * @return The current fuel level
	 */
	public FuelLevel getFuel() {
		return fuel;
	}

	/**
	 * Gets the current cleanliness level of this Rocket.
	 *
	 * @return The current level of cleanliness
	 */
	public Cleanliness getCleanliness() {
		return cleanliness;
	}

	/**
	 * Gets the number of missions completed by this rocket.
	 *
	 * @return The number of completed missions
	 */
	public int getMissionCount() {
		return missionsCompleted;
	}

	/**
	 * Gets the mission progress. If this Rocket is not currently on a mission this
	 * will return zero.
	 *
	 * @return The current mission progress as a percentage
	 */
	public int getMissionProgress() {
		return missionProgressPercent;
	}

	/**
	 * Checks if this Rocket is on a mission.
	 *
	 * @return true if currently on a mission, false otherwise
	 */
	public boolean onMission() {
		return timer.isRunning();
	}

	/**
	 * Refuels this rocket setting its fuel level to {@link FuelLevel#FULL}.
	 * Reports a {@link #ROCKET_STATUS} property change to all listeners.
	 *
	 * @throws IllegalStateException if the rocket cannot be refueled because it is currently
	 * on a mission
	 */
	protected void refuel() {
		if (onMission()) {
			throw new IllegalStateException("Rocket " + name + " cannot be refueled while on a mission");
		}
		if (fuel != FuelLevel.FULL) {
			this.fuel = FuelLevel.FULL;
			pcs.firePropertyChange(ROCKET_STATUS, null, null);
		}
	}

	/**
	 * Cleans this Rocket setting its cleanliness status to {@link Cleanliness#CLEAN}.
	 * Reports a {@link #ROCKET_STATUS} property change to all listeners.
	 *
	 * @throws IllegalStateException if the rocket cannot be cleaned because it is currently
	 * on a mission
	 */
	protected void clean() {
		if (onMission()) {
			throw new IllegalStateException("Rocket " + name + " cannot be cleaned while on a mission");
		}
		if (cleanliness != Cleanliness.CLEAN) {
			this.cleanliness = Cleanliness.CLEAN;
			pcs.firePropertyChange(ROCKET_STATUS, null, null);
		}
	}

	/**
	 * Launches this Rocket on a mission. Reports a {@link #ROCKET_STATUS} property change
	 * to all listeners if launch is successful.
	 *
	 * @throws IllegalStateException if the fuel level is {@link FuelLevel#EMPTY} or if this
	 * rocket is already on a mission
	 */
	protected void launch() throws IllegalStateException {
		if (fuel == FuelLevel.EMPTY) {
			throw new IllegalStateException("Not enough fuel to launch");
		}

		if (timer.isRunning()) {
			throw new IllegalStateException("Rocket: " + name + " is already on a mission");
		}

		timer.start();
		pcs.firePropertyChange(ROCKET_STATUS, null, null);
	}

	/**
	 * Invoked by {@link #timer} every {@link #MISSION_PROGRESS_DELAY_MS} milliseconds
	 * when this Rocket is on a mission.
	 */
	private void onMissionProgress() {
		missionProgressPercent += 5;
		pcs.firePropertyChange(MISSION_PROGRESS, null, null);

		if (missionProgressPercent == 100) {
			missionProgressPercent = 0;
			timer.stop();
			onMissionComplete();
		}
	}

	/**
	 * Called when this Rocket returns from a mission. Fuel is lowered by one level and
	 * cleanliness is set to {@link Cleanliness#DIRTY}. Reports a {@link #MISSION_COMPLETE} property
	 * change followed by a {@link #ROCKET_STATUS} property change to all listeners.
	 */
	private void onMissionComplete() {
		switch (fuel) {
			case EMPTY:
			case LOW:
				fuel = FuelLevel.EMPTY;
				break;
			case FULL:
				fuel = FuelLevel.LOW;
				break;
		}

		cleanliness = Cleanliness.DIRTY;
		missionsCompleted++;

		pcs.firePropertyChange(MISSION_COMPLETE, null, null);
		pcs.firePropertyChange(ROCKET_STATUS, null, null);
	}

	/**
	 * Provides a description of this rocket.
	 *
	 * @return A description including the rocket name and its current state
	 */
	@Override
	public String toString() {
		return "Rocket: " + name + "  On Mission: " + timer.isRunning() + " Fuel level: " + fuel.value +
				"  Cleanliness: " + cleanliness.value;
	}
}
