from flask import Flask, request, url_for, redirect, render_template, session,send_from_directory,flash
import sqlite3
import os
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.secret_key = "exam_repo_system"

UPLOAD_FOLDER = os.path.join(os.getcwd(), "uploads")
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# database (Teacher)
def init_db():
    conn = sqlite3.connect("exam.db")
    cur = conn.cursor()

    cur.execute('''
    CREATE TABLE IF NOT EXISTS teacher (
        username TEXT PRIMARY KEY,
        password TEXT
    )
    ''')
# database(paper)

    cur.execute('''
    CREATE TABLE IF NOT EXISTS papers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    semester TEXT,
    subject TEXT,
    year TEXT,
    filename TEXT
    )
    ''')
    
    cur.execute("INSERT OR IGNORE INTO teacher (username, password) VALUES (?, ?)",
                ("admin", "1234"))
    
    cur.execute('''
    CREATE TABLE IF NOT EXISTS feedback (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    message TEXT
    )
    ''')

    conn.commit()
    conn.close()

init_db()

# dict for AIML BRANCH 
SEM_SUBJECTS_AIML = {
    "1": [
        "Mathematics-I",
        "Engineering Graphics",
        "Engineering Chemistry",
        "English for Communication",
        "Basic Electrical & Electronics Engineering"
    ],
    "2": [
        "Engineering Physics",
        "Mathematics-II",
        "Basic Mechanical Engineering",
        "Basic Civil Engineering & Mechanics",
        "Basic Computer Engineering"
    ],
    "3": [
        "Technical Communication",
        "Introduction to Probability and Statistics",
        "Data Structures",
        "Artificial Intelligence",
        "Object Oriented Programming & Methodology"
    ],
    "4": [
        "Discrete Structures & Linear Algebra",
        "Analysis & Design of Algorithms",
        "Software Engineering",
        "Computer Organization & Architecture",
        "Machine Learning"
    ],
    "5": [
        "DBMS",
        "Operating Systems",
        "Departmental Elective",
    ],
    "6": [
        "Theory of Computation",
        "Computer Networks",
    ],
    "7": [
        "Computer Vision",
        "Departmental Elective",
    ],
    "8": [
        "Business Intelligence",
        "Departmental Elective",
    ]
}

# role selection route
@app.route('/', methods=["GET", "POST"])
def role_select():
    session.clear()
     
    if request.method == "POST":
        role = request.form.get("role")

        if role == "teacher":
            return redirect(url_for('login'))

        elif role == "student":
            session['role'] = 'student'
            return redirect(url_for('home'))

    return render_template('role.html')

# login route
@app.route('/login', methods=["GET", "POST"])
def login():
    if 'teacher' in session:
        return redirect(url_for('home'))

# taking username and password from user
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')

# checking un and pass in db
        conn = sqlite3.connect("exam.db")
        cur = conn.cursor()

        cur.execute("SELECT * FROM teacher WHERE username=? AND password=?",
                    (username, password))
        user = cur.fetchone()

        conn.close()

        if user:
            session['teacher'] = username
            session['role'] = 'teacher'
            return redirect(url_for('home'))

        else:
            flash("Invalid username or password")

    return render_template('login.html')

# home route (selectin which to display teacher or student)
@app.route('/home')
def home():
    role = session.get('role')

    if role == 'teacher':
        return render_template('teacher.html')   

    elif role == 'student':
        return render_template('student.html')

    else:
        return redirect(url_for('role_select'))

# logout
@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('role_select'))

# uploading paper to upload folder
@app.route('/upload', methods=["GET", "POST"])
def upload():
    if 'teacher' not in session:
        return redirect(url_for('login'))

    semester = None
    subjects = []

    if request.method == "POST":
        semester = request.form.get("semester")
        action = request.form.get("action")

        if semester:
            semester = str(semester)
            subjects = SEM_SUBJECTS_AIML.get(semester, [])

        if action == "load":
            return render_template(
                "upload.html",
                subjects=subjects,
                selected_sem=semester
            )

        if action == "upload":
            subject = request.form.get("subject")
            year = request.form.get("year")
            file = request.files.get("file")

            if file and file.filename:
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))

                conn = sqlite3.connect("exam.db")
                cur = conn.cursor()

                cur.execute("""
                INSERT INTO papers (semester, subject, year, filename)
                VALUES (?, ?, ?, ?)
                """, (semester, subject, year, filename))

                conn.commit()
                conn.close()

                flash("Uploaded successfully!")
                return redirect(url_for('home'))

    return render_template("upload.html", subjects=[], selected_sem=None)

@app.route('/papers')
def papers():
    semester = request.args.get('semester')
    subject = request.args.get('subject')

    conn = sqlite3.connect("exam.db")
    cur = conn.cursor()

    papers = []

    if semester or subject:
        query = "SELECT semester, subject, year, filename FROM papers WHERE 1=1"
        params = []

        if semester:
            query += " AND semester=?"
            params.append(semester)

        if subject:
            query += " AND subject=?"
            params.append(subject)

        cur.execute(query, params)
        papers = cur.fetchall()

    conn.close()

    subjects = SEM_SUBJECTS_AIML.get(semester, []) if semester else []

    return render_template("papers.html",papers=papers,subjects=subjects,selected_sem=semester)
    
@app.route('/delete/<filename>')
def delete_file(filename):
    if session.get('role') != 'teacher':
        return "Unauthorized Access"

    import os

    filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)

    if os.path.exists(filepath):
        os.remove(filepath)

    conn = sqlite3.connect("exam.db")
    cur = conn.cursor()
    cur.execute("DELETE FROM papers WHERE filename=?", (filename,))
    conn.commit()
    conn.close()

    return redirect(url_for('papers'))

# view uploaded file
@app.route('/view/<filename>')
def view_file(filename):
    return send_from_directory(
        app.config['UPLOAD_FOLDER'],
        filename
    )

# downold file
@app.route('/download/<filename>')
def download_file(filename):
    filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)

    print("Trying to download:", filepath)
    print("File exists:", os.path.exists(filepath))

    return send_from_directory(
        app.config['UPLOAD_FOLDER'],
        filename,
        as_attachment=True
    )

# taking feedback into database
@app.route('/feedback', methods=["POST"])
def feedback():

    name = request.form.get("name")
    message = request.form.get("message")

    conn = sqlite3.connect("exam.db")
    cur = conn.cursor()

    cur.execute(
        "INSERT INTO feedback (name, message) VALUES (?, ?)",
        (name, message)
    )

    conn.commit()
    conn.close()

    flash("Feedback submitted successfully!")

    return redirect(url_for('role_select'))

if __name__ == '__main__':
    app.run(debug=True)