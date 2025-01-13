# Contributing

This guide will help you set up your environment, make changes, and submit a pull request on Windows.

---

## Prerequisites

Before you begin, ensure you have the following installed on your system:

- **CMake**: A build system generator.
- **Clang++**: The default compiler used in `compile.bat`.
  - If Clang++ is not installed via Visual Studio, update the `-DCMAKE_CXX_COMPILER` path in `compile.bat` to point to your installed Clang++ binary.

---

## Setting Up Your Development Environment

1. Clone the repository:
   `git clone https://github.com/Finding-Fortune/Fortunes-Palette-Compression.git`

2. Create a new branch for your changes:
   `git checkout -b new-branch-name`

---

## Compiling and Running the App

For convenience, `.bat` scripts are provided for Windows. Follow these steps:

1. Compile the project:
   `.\compile.bat`

2. Run the app:
   `.\run.bat`

If you’re not on Windows or prefer manual compilation:
- Use CMake with the Ninja generator and your compiler of choice:
  `cmake -G "Ninja" -DCMAKE_CXX_COMPILER=path-to-clang++ ..`
  `ninja`

---

## Submitting Your Changes

Once you’ve made your changes and verified they work:

1. Stage all changes and commit them:
   `git add --all`
   `git commit -m "Your descriptive commit message"`

2. Push your branch to the remote repository:
   `git push -u origin new-branch-name`

3. Open a pull request:
   - Go to your forked repository on GitHub.
   - Click the "Compare & pull request" button.
   - Add a description of your changes and submit the pull request.

---

## Guidelines for Contributions

To ensure your pull request is accepted, please follow these guidelines:

1. **Write Clear Commit Messages**: Use descriptive commit messages that explain the purpose of the changes.
2. **Adhere to Code Style**: Follow the existing coding style and conventions used in the project.
3. **Test Your Changes**: Ensure your changes don’t introduce bugs and work as intended.
4. **Keep Pull Requests Focused**: Submit separate pull requests for unrelated changes.

---

## Need Help?

If you encounter any issues while setting up the project or submitting a pull request:
- Check the [issues page](https://github.com/Finding-Fortune/Fortunes-Palette-Compression/issues) for known problems.
- Open a new issue if your problem isn’t listed.

We appreciate your contributions and look forward to improving this library with you!

---

## License

By contributing, you agree that your contributions will be licensed under the same [MIT License](LICENSE.md) that covers this project.
