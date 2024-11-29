import os
from crewai import Agent, Task, Crew

from crewai_tools import SerperDevTool
from tools.custom_vertex_tool import vertex_generate_questions  # Import the Vertex AI tool
import yaml
import os

def load_agents():
    """
    Load agent configurations from agents.yaml.
    Returns:
        dict: Loaded agent data.
    """
    file_path = os.path.join(os.path.dirname(__file__), 'config', 'agents.yaml')
    with open(file_path, 'r') as file:
        agents = yaml.safe_load(file)
    return agents

def load_tasks():
    """
    Load task configurations from tasks.yaml.
    Returns:
        dict: Loaded task data.
    """
    file_path = os.path.join(os.path.dirname(__file__), 'config', 'tasks.yaml')
    with open(file_path, 'r') as file:
        tasks = yaml.safe_load(file)
    return tasks
# Set up the Serper and Google credentials
os.environ["SERPER_API_KEY"] = ""
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = r"C:\Users\tejas\Downloads\questionpapergenerator-440603-45edf3359ec2.json"

# Custom Wrapper for SerperDevTool to implement required _run and _arun methods
class CustomSerperTool(SerperDevTool):
    def _run(self, query: str):
        return super().run(query)

    async def _arun(self, query: str):
        return await super().arun(query)

# Initialize the custom Serper tool
serper_tool = CustomSerperTool()

def create_jee_paper_creation_crew(subject, topic):
    # Load agents and tasks from YAML configurations
    agents_config = load_agents()
    tasks_config = load_tasks()

    # Agent 1: Question Researcher with Vertex AI for question generation and Serper for research
    question_researcher = Agent(
        role=agents_config['question_researcher']['role'],
        goal=agents_config['question_researcher']['goal'].replace("{subject}", subject).replace("{topic}", topic),
        backstory=agents_config['question_researcher']['backstory'],
        verbose=True,
        allow_delegation=False,
        tools=[serper_tool, vertex_generate_questions]  # Replaced OpenAI with Vertex AI for generation
    )

    # Agent 2: Question Curator with Serper tool for searching and verification
    question_curator = Agent(
        role=agents_config['question_curator']['role'],
        goal=agents_config['question_curator']['goal'],
        backstory=agents_config['question_curator']['backstory'],
        verbose=True,
        allow_delegation=False,
        tools=[serper_tool]  # Adding only Serper for search functionality
    )

    # Agent 3: Question Paper Formatter with Vertex AI for structuring content
    question_paper_formatter = Agent(
        role=agents_config['question_paper_formatter']['role'],
        goal=agents_config['question_paper_formatter']['goal'],
        backstory=agents_config['question_paper_formatter']['backstory'],
        verbose=True,
        allow_delegation=False,
        tools=[vertex_generate_questions]  # Using Vertex AI for formatting and structuring content
    )

    # Task 1: Research Task assigned to Question Researcher
    research_task = Task(
        description=tasks_config['research_task']['description'].replace("{subject}", subject).replace("{topic}", topic),
        expected_output=tasks_config['research_task']['expected_output'],
        agent=question_researcher
    )

    # Task 2: Curation Task assigned to Question Curator
    curation_task = Task(
        description=tasks_config['curation_task']['description'],
        expected_output=tasks_config['curation_task']['expected_output'],
        agent=question_curator
    )

    # Task 3: Formatting Task assigned to Question Paper Formatter
    formatting_task = Task(
        description=tasks_config['formatting_task']['description'],
        expected_output=tasks_config['formatting_task']['expected_output'],
        agent=question_paper_formatter
    )

    # Create the crew with agents and tasks
    return Crew(
        agents=[question_researcher, question_curator, question_paper_formatter],
        tasks=[research_task, curation_task, formatting_task]
    )

