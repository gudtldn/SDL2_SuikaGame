import os
import xml.etree.ElementTree as ET
from collections import defaultdict
from typing import TypedDict

class IncludeFiles(TypedDict):
    c: list[str]
    h: list[str]

def find_source_files(directory: str) -> IncludeFiles:
    include_files: IncludeFiles = defaultdict(list) # type: ignore

    # 디렉토리 내의 모든 .c, .h 파일을 찾아서 분류
    for root, dirs, files in os.walk(directory):
        root = root.replace("\\", "/").split("/")[-1]
        for file in files:
            if file.endswith(".c"):
                include_files['c'].append(f"{root}/{file}")
            elif file.endswith(".h"):
                include_files['h'].append(f"{root}/{file}")

    return include_files

def update_vcxproj(vcxproj_path: str, include_files: IncludeFiles) -> None:
    tree = ET.parse(vcxproj_path)
    root = tree.getroot()

    # XML 네임스페이스 처리
    ns = {"": "http://schemas.microsoft.com/developer/msbuild/2003"}
    ET.register_namespace("", ns[""])

    # ClCompile 항목 업데이트
    clcompile_group = root.find(".//ItemGroup[ClCompile]", ns)
    if clcompile_group is None:
        clcompile_group = ET.SubElement(root, "ItemGroup")
    else:
        clcompile_group.clear()

    for file in include_files['c']:
        ET.SubElement(clcompile_group, "ClCompile", Include=file)

    # ClInclude 항목 업데이트
    clinclude_group = root.find(".//ItemGroup[ClInclude]", ns)
    if clinclude_group is None:
        clinclude_group = ET.SubElement(root, "ItemGroup")
    else:
        clinclude_group.clear()

    for file in include_files['h']:
        ET.SubElement(clinclude_group, "ClInclude", Include=file)

    # 변경사항 저장
    tree.write(vcxproj_path, encoding="utf-8", xml_declaration=True)

def update_vcxproj_filters(vcxproj_filters_path: str, include_files: IncludeFiles) -> None:
    tree = ET.parse(vcxproj_filters_path)
    root = tree.getroot()

    ns = {"": "http://schemas.microsoft.com/developer/msbuild/2003"}
    ET.register_namespace("", ns[""])

    # 기존 필터 정의 유지
    filter_group = root.find(".//ItemGroup[Filter]", ns)
    if filter_group is None:
        filter_group = ET.SubElement(root, "ItemGroup")
        ET.SubElement(filter_group, "Filter", Include="소스 파일")
        ET.SubElement(filter_group, "Filter", Include="헤더 파일")

    # ClCompile 항목 업데이트
    clcompile_group = root.find(".//ItemGroup[ClCompile]", ns)
    if clcompile_group is None:
        clcompile_group = ET.SubElement(root, "ItemGroup")
    else:
        clcompile_group.clear()

    for file in include_files['c']:
        item = ET.SubElement(clcompile_group, "ClCompile", Include=file)
        ET.SubElement(item, "Filter").text = "소스 파일"

    # ClInclude 항목 업데이트
    clinclude_group = root.find(".//ItemGroup[ClInclude]", ns)
    if clinclude_group is None:
        clinclude_group = ET.SubElement(root, "ItemGroup")
    else:
        clinclude_group.clear()

    for file in include_files['h']:
        item = ET.SubElement(clinclude_group, "ClInclude", Include=file)
        ET.SubElement(item, "Filter").text = "헤더 파일"

    tree.write(vcxproj_filters_path, encoding="utf-8", xml_declaration=True)

if __name__ == "__main__":
    source_directory = "./SDLGameProject/Source"                             # 소스 파일이 있는 디렉토리
    vcxproj_path = "./SDLGameProject/SDLGameProject.vcxproj"                 # .vcxproj 파일 경로
    vcxproj_filters_path = "./SDLGameProject/SDLGameProject.vcxproj.filters" # .vcxproj.filters 파일 경로

    include_files = find_source_files(source_directory)
    update_vcxproj(vcxproj_path, include_files)
    update_vcxproj_filters(vcxproj_filters_path, include_files)
    print("프로젝트 파일과 필터 파일이 성공적으로 업데이트되었습니다.")
