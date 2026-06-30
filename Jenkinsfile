pipeline {

    agent any

    options {
        timestamps()
    }

    environment {
        BUILD_DIR = "build"
    }

    stages {

        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Configure') {
            steps {
                sh '''
                    rm -rf ${BUILD_DIR}
                    mkdir -p ${BUILD_DIR}
                    cd ${BUILD_DIR}

                    cmake .. \
                        -DCMAKE_BUILD_TYPE=Debug \
                        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
                '''
            }
        }

        stage('Build') {
            steps {
                sh '''
                    cd ${BUILD_DIR}
                    make -j$(nproc)
                '''
            }
        }

        stage('Verify Build') {
            steps {
                sh '''
                    echo "Current directory:"
                    pwd

                    echo "Build directory:"
                    ls -la ${BUILD_DIR}

                    echo "Checking compile_commands.json..."
                    test -f ${BUILD_DIR}/compile_commands.json

                    ls -l ${BUILD_DIR}/compile_commands.json
                '''
            }
        }

        stage('SonarQube Analysis') {
            steps {
                script {
                    def scannerHome = tool 'SonarScanner'

                    withSonarQubeEnv('SonarQube') {
                        sh """
                            ${scannerHome}/bin/sonar-scanner
                        """
                    }
                }
            }
        }

        stage('Quality Gate') {
            steps {
                timeout(time: 5, unit: 'MINUTES') {
                    waitForQualityGate abortPipeline: true
                }
            }
        }

        stage('Unit Tests') {
            steps {
                sh '''
                    cd ${BUILD_DIR}
                    ctest -L unit --output-on-failure
                '''
            }
        }

        stage('Integration Tests') {
            steps {
                sh '''
                    cd ${BUILD_DIR}
                    ctest -L integration --output-on-failure
                '''
            }
        }

        stage('Package') {
            when {
                buildingTag()
            }
            steps {
                sh '''
                    chmod +x scripts/package.sh
                    ./scripts/package.sh ${TAG_NAME}
                '''
            }
        }

        stage('Archive') {
            when {
                buildingTag()
            }
            steps {
                archiveArtifacts artifacts: '*.tar.gz', fingerprint: true
            }
        }
    }

    post {
        success {
            echo 'Pipeline completed successfully.'
        }

        failure {
            echo 'Pipeline failed.'
        }

        always {
            cleanWs()
        }
    }
}
