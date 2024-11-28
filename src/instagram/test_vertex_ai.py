from google.cloud import aiplatform

# Initialize the Vertex AI SDK
aiplatform.init(project="your-project-id", location="us-central1")

# Specify and load the pre-trained model
model = aiplatform.TextGenerationModel.from_pretrained("text-bison")

# Generate a response
response = model.predict(prompt="Generate a question for JEE Physics.", temperature=0.7)
print(response.text)
