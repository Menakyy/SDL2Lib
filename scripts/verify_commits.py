import subprocess
import sys
from typing import List

correct_commit_messages: List[str] = [
    "[fix]",
    "[feat]",
    "[other]",
    "[docs]",
    "[style]",
    "[refactor]",
    "[test]",
]

invalid_commit_messages: List[str] = []


def main() -> None:
    base_branch = "develop"
    try:
        subprocess.run(["git", "fetch", "origin", base_branch], check=True)
    except subprocess.CalledProcessError:
        print(f"Branch '{base_branch}' does not exist on origin.")
        sys.exit(1)

    result = subprocess.run(
        ["git", "log", "origin/develop..HEAD", "--oneline"],
        capture_output=True,
        text=True,
    )

    lines: List[str] = result.stdout.strip().splitlines()

    invalid = False
    for line in lines:
        commit_hash, commit_message = line.split(" ", 1)
        if not any(
            commit_message.startswith(prefix) for prefix in correct_commit_messages
        ):
            invalid_commit_messages.append(commit_message)
            invalid = True

    if invalid:
        print("\nERROR! The following commit messages are invalid:\n")
        for message in invalid_commit_messages:
            print(f"- {message}")
        print()
        sys.exit(1)

    print("\nAll commit messages are valid!\n")


if __name__ == "__main__":
    main()
