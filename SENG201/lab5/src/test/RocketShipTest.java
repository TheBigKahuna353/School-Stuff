package test;

import app.RocketShip;
import static org.junit.Assert.*;


import org.junit.Test;

public class RocketShipTest {

	@Test
    public void fuelUpTest() {
        RocketShip testRocketShip = new RocketShip(50);
        testRocketShip.fuelUp(30);
        assertEquals(80, testRocketShip.getFuelLevel());
    }

    @Test
    public void takeOffTest() {
        RocketShip testRocketShip = new RocketShip(50);
        testRocketShip.takeOff();
        assertEquals(30, testRocketShip.getFuelLevel());
        assertEquals(20, testRocketShip.getCurrentHeight());
    }
}