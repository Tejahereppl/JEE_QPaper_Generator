# main.py

from crew import create_jee_paper_creation_crew





# Get user input (you can replace this with dynamic input if using a CLI or form)
subject = input("Enter the subject (e.g., Physics, Chemistry, Mathematics): ")
topic = input("Enter the topic (e.g., Electromagnetism): ")

# Create the crew with the specified subject and topic
jee_paper_creation_crew = create_jee_paper_creation_crew(subject, topic)

# Kick off the crew with the user-specified inputs
result = jee_paper_creation_crew.kickoff(inputs={'subject': subject, 'topic': topic})
print(result)
