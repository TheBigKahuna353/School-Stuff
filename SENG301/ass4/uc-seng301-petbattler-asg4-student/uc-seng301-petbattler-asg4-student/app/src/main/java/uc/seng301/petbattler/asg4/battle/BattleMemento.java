package uc.seng301.petbattler.asg4.battle;



public class BattleMemento {
    private final Team leftTeam;
    private final Team rightTeam;

    public BattleMemento(Team leftTeam, Team rightTeam) {
        this.leftTeam = leftTeam.clone();
        this.rightTeam = rightTeam.clone();
    }

    public Team getLeftTeam() {
        return leftTeam;
    }

    public Team getRightTeam() {
        return rightTeam;
    }
}
