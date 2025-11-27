import requests
import json

# Local LM Studio server URL
API_URL = "http://127.0.0.1:1234/v1/chat/completions"

# Model name
MODEL_NAME = "phi-4-mini"

# Conversation history (memory)
messages = [
    {"role": "system", "content": "You are Phi-4 Mini, a helpful and expert coding assistant who explains clearly and fixes bugs."}
]

def chat_with_phi4(user_input):
    """Send message + conversation history to local model and get reply."""
    messages.append({"role": "user", "content": user_input})

    data = {
        "model": MODEL_NAME,
        "messages": messages
    }

    try:
        response = requests.post(API_URL, headers={"Content-Type": "application/json"}, data=json.dumps(data))
        if response.status_code == 200:
            result = response.json()
            reply = result["choices"][0]["message"]["content"]
            messages.append({"role": "assistant", "content": reply})
            return reply
        else:
            return f"⚠️ Error {response.status_code}: {response.text}"

    except Exception as e:
        return f"❌ Connection error: {str(e)}"


print("🤖 Phi-4 Mini Chatbot Ready! Type 'exit' or 'quit' to stop.\n")

while True:
    user_input = input("You: ")
    if user_input.lower() in ["exit", "quit"]:
        print("👋 Goodbye!")
        break
    reply = chat_with_phi4(user_input)
    print(f"🤖 Bot: {reply}\n")