package To_Do_List;

import javax.swing.*;
import java.awt.*;

@SuppressWarnings("serial")
public class ToDoListGUI extends JFrame {
    private TaskManager manager;
    private DefaultListModel<String> listModel;
    private JList<String> taskList;
    private JTextField inputField;

    public ToDoListGUI() {
        manager = new TaskManager();
        listModel = new DefaultListModel<>();

        setTitle("Smart To-Do List");
        setSize(400, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        inputField = new JTextField();
        JButton addButton = new JButton("Add Task");
        JButton deleteButton = new JButton("Delete");
        JButton toggleButton = new JButton("Toggle Complete");

        JPanel topPanel = new JPanel(new BorderLayout());
        topPanel.add(inputField, BorderLayout.CENTER);
        topPanel.add(addButton, BorderLayout.EAST);

        taskList = new JList<>(listModel);
        JScrollPane scrollPane = new JScrollPane(taskList);

        JPanel bottomPanel = new JPanel();
        bottomPanel.add(toggleButton);
        bottomPanel.add(deleteButton);

        add(topPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);
        add(bottomPanel, BorderLayout.SOUTH);

        // Add task
        addButton.addActionListener(e -> {
            String text = inputField.getText();
            if (!text.isEmpty()) {
                manager.addTask(new Task(text));
                refreshList();
                inputField.setText("");
            }
        });

        // Delete task
        deleteButton.addActionListener(e -> {
            int index = taskList.getSelectedIndex();
            if (index >= 0) {
                manager.removeTask(index);
                refreshList();
            }
        });

        // Toggle completion
        toggleButton.addActionListener(e -> {
            int index = taskList.getSelectedIndex();
            if (index >= 0) {
                manager.getTasks().get(index).toggleCompleted();
                refreshList();
            }
        });

        setVisible(true);
    }

    private void refreshList() {
        listModel.clear();
        for (Task t : manager.getTasks()) {
            listModel.addElement(t.toString());
        }
    }

    public static void main(String[] args) {
        new ToDoListGUI();
    }
}

