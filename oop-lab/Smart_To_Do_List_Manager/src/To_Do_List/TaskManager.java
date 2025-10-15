package To_Do_List;

import java.util.ArrayList;

public class TaskManager {
    private ArrayList<Task> tasks;

    public TaskManager() {
        tasks = new ArrayList<>();
    }

    public void addTask(Task task) { tasks.add(task); }
    public void removeTask(int index) { tasks.remove(index); }
    public ArrayList<Task> getTasks() { return tasks; }
}

