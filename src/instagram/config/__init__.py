# config/__init__.py
import yaml
import os

# Load agents from agents.yaml
def load_agents():
    file_path = os.path.join(os.path.dirname(__file__), 'agents.yaml')
    with open(file_path, 'r') as file:
        agents = yaml.safe_load(file)
    return agents

# Load tasks from tasks.yaml
def load_tasks():
    file_path = os.path.join(os.path.dirname(__file__), 'tasks.yaml')
    with open(file_path, 'r') as file:
        tasks = yaml.safe_load(file)
    return tasks
