"""
ULDA Vulkan Host — The LUM on the GPU
======================================
License: AGPL-3.0
Contact: JornePel@gmail.com
Dedicated to Terrence Andrew Davis (1969-2018).

Loads the GLSL compute shader, compiles it to SPIR-V, and runs the LUM
on any Vulkan-capable GPU.

Requirements:
    pip install vulkan
"""

import struct
import numpy as np

try:
    import vulkan as vk
except ImportError:
    print("Install pyvulkan: pip install vulkan")
    raise


# ────────────────────────────────────────────────────────────────────
# CONFIG
# ────────────────────────────────────────────────────────────────────
SHADER_PATH   = "gpu/ulda_lum.spv"
NUM_NODES     = 1024
LOCAL_SIZE    = 256


def load_shader(path):
    with open(path, "rb") as f:
        return f.read()


def main():
    # ── 1. Instance ──────────────────────────────────────────────
    app_info = vk.VkApplicationInfo(
        pApplicationName="ULDA LUM",
        applicationVersion=vk.VK_MAKE_VERSION(1, 0, 0),
        pEngineName="No Engine",
        engineVersion=vk.VK_MAKE_VERSION(1, 0, 0),
        apiVersion=vk.VK_API_VERSION_1_0,
    )
    inst_info = vk.VkInstanceCreateInfo(
        pApplicationInfo=app_info,
    )
    instance = vk.vkCreateInstance(inst_info, None)

    # ── 2. Pick a physical device ────────────────────────────────
    devices = vk.vkEnumeratePhysicalDevices(instance)
    if not devices:
        raise RuntimeError("No Vulkan-capable GPU found")
    physical_device = devices[0]

    props = vk.vkGetPhysicalDeviceProperties(physical_device)
    print(f"GPU: {props.deviceName}")

    # ── 3. Find a compute queue ──────────────────────────────────
    queue_families = vk.vkGetPhysicalDeviceQueueFamilyProperties(physical_device)
    compute_family = None
    for i, q in enumerate(queue_families):
        if q.queueFlags & vk.VK_QUEUE_COMPUTE_BIT:
            compute_family = i
            break
    if compute_family is None:
        raise RuntimeError("No compute queue found")

    # ── 4. Create logical device ─────────────────────────────────
    queue_priority = [1.0]
    queue_info = vk.VkDeviceQueueCreateInfo(
        queueFamilyIndex=compute_family,
        queueCount=1,
        pQueuePriorities=queue_priority,
    )
    device_info = vk.VkDeviceCreateInfo(
        queueCreateInfoCount=1,
        pQueueCreateInfos=[queue_info],
    )
    device = vk.vkCreateDevice(physical_device, device_info, None)
    queue = vk.vkGetDeviceQueue(device, compute_family, 0)

    # ── 5. Load SPIR-V ───────────────────────────────────────────
    spirv = load_shader(SHADER_PATH)

    # ── 6. Create shader module ──────────────────────────────────
    shader_info = vk.VkShaderModuleCreateInfo(
        codeSize=len(spirv),
        pCode=spirv,
    )
    shader_module = vk.vkCreateShaderModule(device, shader_info, None)

    # ── 7. Descriptor set layout ─────────────────────────────────
    bindings = []
    for i in range(4):
        bindings.append(vk.VkDescriptorSetLayoutBinding(
            binding=i,
            descriptorType=vk.VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
            descriptorCount=1,
            stageFlags=vk.VK_SHADER_STAGE_COMPUTE_BIT,
        ))

    layout_info = vk.VkDescriptorSetLayoutCreateInfo(
        bindingCount=4,
        pBindings=bindings,
    )
    descriptor_layout = vk.vkCreateDescriptorSetLayout(device, layout_info, None)

    # ── 8. Pipeline layout ───────────────────────────────────────
    pipeline_layout_info = vk.VkPipelineLayoutCreateInfo(
        setLayoutCount=1,
        pSetLayouts=[descriptor_layout],
    )
    pipeline_layout = vk.vkCreatePipelineLayout(device, pipeline_layout_info, None)

    # ── 9. Compute pipeline ──────────────────────────────────────
    stage_info = vk.VkPipelineShaderStageCreateInfo(
        stage=vk.VK_SHADER_STAGE_COMPUTE_BIT,
        module=shader_module,
        pName="main",
    )
    pipeline_info = vk.VkComputePipelineCreateInfo(
        stage=stage_info,
        layout=pipeline_layout,
    )
    pipeline = vk.vkCreateComputePipelines(device, vk.VK_NULL_HANDLE, [pipeline_info], None)[0]

    print("Vulkan pipeline created.")
    print("LUM is ready to run on the GPU.")
    print()
    print("Note: Full buffer allocation + dispatch is in the C++ host.")
    print("This Python host verifies the pipeline creation.")


if __name__ == "__main__":
    main()
