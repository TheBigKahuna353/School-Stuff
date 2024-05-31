package uc.seng301.petbattler.asg4.battle;

import java.util.Stack;

// Caretaker
public class GameInvoker {
    private final Stack<BattleMemento> undoStack = new Stack<>();
    private final Stack<BattleMemento> redoStack = new Stack<>();

    public void saveState(BattleRunner battleRunner) {
        undoStack.push(battleRunner.saveStateToMemento());
    }

    public void undo(BattleRunner battleRunner) {
        if (!undoStack.isEmpty()) {
            BattleMemento memento = undoStack.pop();
            redoStack.push(battleRunner.saveStateToMemento());
            battleRunner.getStateFromMemento(memento);
        }
    }

    public void redo(BattleRunner battleRunner) {
        if (!redoStack.isEmpty()) {
            BattleMemento memento = redoStack.pop();
            undoStack.push(battleRunner.saveStateToMemento());
            battleRunner.getStateFromMemento(memento);
        }
    }
}