package To_Do_List;

public class Task {
    private String title;
    private boolean completed;

    public Task(String title) {
        this.title = title;
        this.completed = false;
    }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public boolean isCompleted() { return completed; }
    public void toggleCompleted() { this.completed = !this.completed; }

    @Override
    public String toString() {
        return (completed ? "[✓] " : "[ ] ") + title;
    }
}

