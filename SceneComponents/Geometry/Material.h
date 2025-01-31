#ifndef HAYA_LUZ_MATERIAL_H
#define HAYA_LUZ_MATERIAL_H

#include "../../Utilities/Vector3.h"

class Material {
private:
    Vector3 diffuseIntensity;
    Vector3 specularIntensity;
    Vector3 emissionIntensity;
    double diffuse;
    double specular;
    double glossiness;
    double emissivity;
    double transmission;
    double refractionIndex;

public:
    Material() :
        diffuseIntensity(Vector3(0.5, 0.5, 0.5)),
        specularIntensity(Vector3(0.5, 0.5, 0.5)),
        emissionIntensity(Vector3(0.1, 0.1, 0.1)),
        diffuse(0.5),
        specular(0.5),
        glossiness(0.5),
        emissivity(0.1),
        transmission(0),
        refractionIndex(1) {}
    
    Material(const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& emissionIntensity,
             const double diffuse, const double specular, const double glossiness, const double emissivity) :
        diffuseIntensity(diffuseIntensity),
        specularIntensity(specularIntensity),
        emissionIntensity(Vector3(0, 0, 0)),
        diffuse(diffuse),
        specular(specular),
        glossiness(glossiness),
        emissivity(emissivity),
        transmission(0),
        refractionIndex(1) {}
    
    Material(const Vector3& diffuseIntensity, const Vector3& specularIntensity, const Vector3& emissionIntensity,
             const double diffuse, const double specular, const double glossiness, const double emissivity,
             const double transmission, const double refractionIndex) :
        diffuseIntensity(diffuseIntensity),
        specularIntensity(specularIntensity),
        emissionIntensity(emissionIntensity),
        diffuse(diffuse),
        specular(specular),
        glossiness(glossiness),
        emissivity(emissivity),
        transmission(transmission),
        refractionIndex(refractionIndex) {}
    
    const Vector3& getDiffuseIntensity() const {
        return diffuseIntensity;
    }

    const Vector3& getSpecularIntensity() const {
        return specularIntensity;
    }

    double getDiffuse() const {
        return diffuse;
    }

    double getSpecular() const {
        return specular;
    }

    double getGlossiness() const {
        return glossiness;
    }

    double getAmbient() const {
        return emissivity;
    }

    double getTransmission() const {
        return transmission;
    }

    double getRefractionIndex() const {
        return refractionIndex;
    }

    void setDiffuseIntensity(const Vector3& newDiffuseIntensity) {
        diffuseIntensity = newDiffuseIntensity;
    }

    void setSpecularIntensity(const Vector3& newSpecularIntensity) {
        specularIntensity = newSpecularIntensity;
    }

    void setDiffuse(const double newDiffuse) {
        diffuse = newDiffuse;
    }

    void setSpecular(const double newSpecular) {
        specular = newSpecular;
    }

    void setGlossiness(const double newGlossiness) {
        glossiness = newGlossiness;
    }

    void setAmbient(const double newAmbient) {
        emissivity = newAmbient;
    }

    void setTransmission(const double newTransmission) {
        transmission = newTransmission;
    }

    void setRefractionIndex(const double newRefractionIndex) {
        refractionIndex = newRefractionIndex;
    }

    friend std::ostream &operator<<(std::ostream& os, const Material& material) {
        os << "Material:" << std::endl
           << "    diffuseIntensity: " << material.getDiffuseIntensity() << std::endl
           << "    specularIntensity: " << material.getSpecularIntensity() << std::endl
           << "    diffuse: " << material.getDiffuse() << std::endl
           << "    specular: " << material.getSpecular() << std::endl
           << "    glossiness: " << material.getGlossiness() << std::endl
           << "    ambient: " << material.getAmbient() << std::endl
           << "    transmission: " << material.getTransmission() << std::endl
           << "    refractionIndex: " << material.getRefractionIndex() << std::endl;
        
        return os;
    }
};

#endif //HAYA_LUZ_MATERIAL_H