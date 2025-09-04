import pypandoc

input_path = "./Project D.pdf"
output_path = "./Project_D.md"

# Convert PDF to Markdown
pypandoc.convert_text(
    text=open(input_path, "rb").read(),
    format="pdf",
    to="md",
    outputfile=output_path,
    extra_args=['--standalone']
)
