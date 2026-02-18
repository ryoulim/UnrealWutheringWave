import os
import codecs

# === 설정 ===
# 이 파이썬 파일이 있는 폴더를 프로젝트 루트로 사용
PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))

TARGET_EXTENSIONS = {".h", ".cpp"}

def convert_file_to_utf8_bom(file_path):
    try:
        with open(file_path, "rb") as f:
            raw = f.read()

        # 이미 UTF-8 BOM이면 스킵
        if raw.startswith(codecs.BOM_UTF8):
            return False

        # 인코딩 추정
        for encoding in ("utf-8", "cp949", "euc-kr", "latin1"):
            try:
                text = raw.decode(encoding)
                break
            except UnicodeDecodeError:
                continue
        else:
            print(f"[SKIP] 인코딩 판독 실패: {file_path}")
            return False

        # UTF-8 BOM으로 다시 저장
        with open(file_path, "wb") as f:
            f.write(codecs.BOM_UTF8)
            f.write(text.encode("utf-8"))

        print(f"[OK] 변환 완료: {file_path}")
        return True

    except Exception as e:
        print(f"[ERROR] {file_path} -> {e}")
        return False


def main():
    converted = 0
    skipped = 0

    print(f"대상 루트 폴더: {PROJECT_ROOT}\n")

    for root, _, files in os.walk(PROJECT_ROOT):
        for file in files:
            ext = os.path.splitext(file)[1].lower()
            if ext in TARGET_EXTENSIONS:
                path = os.path.join(root, file)
                if convert_file_to_utf8_bom(path):
                    converted += 1
                else:
                    skipped += 1

    print("\n=== 완료 ===")
    print(f"변환됨: {converted}")
    print(f"스킵됨: {skipped}")


if __name__ == "__main__":
    main()
