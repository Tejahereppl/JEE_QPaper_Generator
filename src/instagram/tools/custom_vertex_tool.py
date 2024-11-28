# tools/custom_vertex_tool.py
from google.cloud import aiplatform
import vertexai

from crewai_tools import tool

# Initialize Vertex AI SDK

vertexai.init(project='questionpapergenerator-440603', location='us-central1')
from vertexai.generative_models import GenerativeModel




@tool
def vertex_generate_questions(prompt: str) -> str:
    """
    Custom function to use Vertex AI for generating questions.
    
    Args:
        prompt (str): The prompt for Vertex AI to generate questions based on the input topic.
        
    Returns:
        str: Response from the Vertex AI model with the generated questions.
    """
    # Define the model ID and temperature for Vertex AI
    model = GenerativeModel("gemini-pro")  # Replace with your Vertex model ID if needed

    # Make the prediction using the prompt
    response = model.predict(prompt=prompt, temperature=0.7)

    # Return the generated text
    return response.text
